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
	move_pitch_cmd_ = jconfig["geonosis_commands"].get<json>()["MOVE_PITCH"].get<std::string>();
	move_yaw_cmd_ = jconfig["geonosis_commands"].get<json>()["MOVE_YAW"].get<std::string>();
	detect_cam_cmd_ = jconfig["geonosis_commands"].get<json>()["DETECT_CAM"].get<std::string>();
	detect_stages_cmd_ = jconfig["geonosis_commands"].get<json>()["DETEC_STAGE"].get<std::string>();
	stop_cmd_ = jconfig["geonosis_commands"].get<json>()["STOP_ACQUISITION"].get<std::string>();
	show_frame_acquisition_cmd_ = jconfig["geonosis_commands"].get<json>()["SHOW_FRAME_ACQUISITION"].get<std::string>();
	show_pantilt_pos_cmd_ = jconfig["geonosis_commands"].get<json>()["PANTILT_POS"].get<std::string>();
	show_cam_id_cmd_ = jconfig["geonosis_commands"].get<json>()["SHOW_CAM_ID"].get<std::string>();
	set_sweep_angle_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_SWEEP_ANGLE"].get<std::string>();
	set_initial_pos_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_INITIAL_POS"].get<std::string>();
	set_overlay_percent_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_OVERLAY_PERCENTAGE"].get<std::string>();
	set_scan_number_lines_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_SCAN_NUM_LINES"].get<std::string>();
	set_integration_time_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_INTEGRATION_TIME"].get<std::string>();
	set_frame_period_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_FRAME_PERIOD"].get<std::string>();
	set_return_speed_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_RETURN_SPEED"].get<std::string>();
	set_primary_cam_cmd_ = jconfig["geonosis_commands"].get<json>()["SET_PRIMARY_CAM"].get<std::string>();

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

	if (command.compare(move_pitch_cmd_) == 0) {
		//hyspex_control_->movePitch();  // need parameters
	}

	if (command.compare(move_yaw_cmd_) == 0) {
		//hyspex_control_->moveYaw(); // need parameters
	}

	if (command.compare(detect_cam_cmd_) == 0) {
		hyspex_control_->detectCamera();
	}

	if (command.compare(detect_stages_cmd_) == 0) {
		hyspex_control_->detectStages();
	}

	if (command.compare(stop_cmd_) == 0) {
		hyspex_control_->stopAquisition();
	}

	if (command.compare(show_frame_acquisition_cmd_) == 0) {
		hyspex_control_->showFrameAquisition();
	}

	if (command.compare(show_pantilt_pos_cmd_) == 0) {
		hyspex_control_->showPanTiltPosition();
	}

	if (command.compare(show_cam_id_cmd_) == 0) {
		hyspex_control_->showCamIds();
	}

	if (command.compare(set_sweep_angle_cmd_) == 0) {
		//hyspex_control_->setSweepAngle(); // need parameters
	}

	if (command.compare(set_initial_pos_cmd_) == 0) {
		//hyspex_control_->setInitialPosition(); // need parameters
	}

	if (command.compare(set_overlay_percent_cmd_) == 0) {
		//hyspex_control_->setOverlayPercentage(); // need parameters
	}

	if (command.compare(set_scan_number_lines_cmd_) == 0) {
		//hyspex_control_->setScanNumberLines(); // need parameters
	}

	if (command.compare(set_integration_time_cmd_) == 0) {
		//hyspex_control_->setInitialPosition(); // need parameters
	}

	if (command.compare(set_frame_period_cmd_) == 0) {
		//hyspex_control_->setFramePeriod(); // need parameters
	}

	if (command.compare(set_return_speed_cmd_) == 0) {
		//hyspex_control_->setReturnSpeed(); // need parameters
	}

	if (command.compare(set_primary_cam_cmd_) == 0) {
		//hyspex_control_->setPrimaryCam(); // need parameters
	}

	std_msgs::String ros_str;
	ros_str.data = "It's works!";
	return ros_str;
}


