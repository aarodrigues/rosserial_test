#include "NodeControl.h"
#include<iostream>
#include <windows.h>

NodeControl::NodeControl() :
	synch_(false),
	ack_(false),
	hyspex_control_(std::unique_ptr<HySpexControl>(new HySpexControl())),
	enable_angle_(true),
	enable_status_(true),
	enable_publishing_(false)
{
	if (loadParameters())
		initRosMaster();
	else
		exit(0);
}

NodeControl::~NodeControl()
{
}

bool NodeControl::jsonConfig(json &jconfig){
	std::ifstream file("config\\config.json");

	if (!file.is_open())
	{
		std::cout << "Unable to open json config file." << std::endl;
		return false;
	}

	file >> jconfig;
	return true;
}

bool NodeControl::loadParameters() {
	json jconfig;
	bool success = jsonConfig(jconfig);

	/* Configure ros master ip from json file */
	ros_ip_ = jconfig["ros_master_ip"].get<json>()["IP"].get<std::string>();

	/* load topics name from json file */
	start_topic_ = jconfig["ros_topics"].get<json>()["START"].get<std::string>();
	angles_pantilt_topic_ = jconfig["ros_topics"].get<json>()["ANGLES_PANTILT"].get<std::string>();
	confirm_start_topic_ = jconfig["ros_topics"].get<json>()["CONFIRM_START"].get<std::string>();
	second_confirmation_topic_ = jconfig["ros_topics"].get<json>()["SECOND_CONFIRMATION"].get<std::string>();
	status_topic_ = jconfig["ros_topics"].get<json>()["STATUS"].get<std::string>();
	command_topic_ = jconfig["ros_topics"].get<json>()["COMMAND"].get<std::string>();

	/* load command names from json file */
	start_cmd_ = jconfig["geonosis_commands"].get<json>()["START_ACQUISITION"].get<std::string>();

	return success;
}

void NodeControl::initRosMaster() {
	/* Convert std::string to char* */
	std::vector<char> writable(ros_ip_.begin(), ros_ip_.end());
	writable.push_back('\0');
	/* set ROS master ip */
	ros_master_ = &*writable.begin();
	std::cout << "Connecting to server at " << ros_master_ << std::endl;
	nh_.initNode(ros_master_);
}

void NodeControl::listener() {
	acknowledging_.data = "true";

	ros::Publisher ack_pub(confirm_start_topic_.c_str(), &acknowledging_);
	nh_.advertise(ack_pub);

	ros::Publisher pantilt_pub(angles_pantilt_topic_.c_str(), &angles_);
	nh_.advertise(pantilt_pub);

	ros::Publisher status_pub(status_topic_.c_str(), &log_);
	nh_.advertise(status_pub);

	while (true)
	{
		if (synch_) {
			if (!ack_) {
				ack_pub.publish(&acknowledging_);
				enable_publishing_ = true;
			}
			if (enable_publishing_ && enable_angle_) {
				std::string str = hyspex_control_->getPanTilt();
				angles_.data = str.c_str();
				pantilt_pub.publish(&angles_);
			}
			if (enable_publishing_ && enable_status_) {
				std::string str = hyspex_control_->getLog();
				log_.data = str.c_str();
				status_pub.publish(&log_);
			}
		}
		nh_.spinOnce();
		Sleep(100);
	}
}

std_msgs::String NodeControl::callback(const std_msgs::String &msg) {
	std::cout << "Message received: " << msg.data << std::endl;
	std::string command = msg.data;

	if (command.compare(start_cmd_) == 0) {
		hyspex_control_->startAquisition();
	}

	std_msgs::String ros_str;
	ros_str.data = "It's works!";
	return ros_str;
}


