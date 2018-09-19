#include "NodeControl.h"
#include<iostream>
#include <windows.h>

NodeControl::NodeControl(char *master_ip) :
	m_ros_master_(master_ip),
	synch_(false),
	ack_(false),
	hyspex_control_(std::unique_ptr<HySpexControl>(new HySpexControl())),
	enable_angle_(true),
	enable_status_(true),
	enable_perpetual_publishing_(false)
{
}


NodeControl::~NodeControl()
{
}


void NodeControl::initRosMaster() {
	std::cout << "Connecting to server at " << m_ros_master_ << std::endl;
	nh_.initNode(m_ros_master_);
}

void NodeControl::listener() {
	acknowledging_.data = "true";

	ros::Publisher ack_pub(CONFIRM_START, &acknowledging_);
	nh_.advertise(ack_pub);

	ros::Publisher pantilt_pub(ANGLES_PANTILT, &angles_);
	nh_.advertise(pantilt_pub);

	ros::Publisher status_pub(STATUS, &status_);
	nh_.advertise(status_pub);

	while (true)
	{
		if (synch_) {
			if (!ack_) {
				ack_pub.publish(&acknowledging_);
				enable_perpetual_publishing_ = true;
			}
			if (enable_perpetual_publishing_ && enable_angle_) {
				std::string str = hyspex_control_->detectCamera();
				angles_.data = str.c_str();
				pantilt_pub.publish(&angles_);
			}
			if (enable_perpetual_publishing_ && enable_status_) {
				std::string str = hyspex_control_->detectCamera();
				status_.data = str.c_str();
				status_pub.publish(&status_);
			}
		}
		nh_.spinOnce();
		Sleep(100);
	}
}

std_msgs::String NodeControl::callback(const std_msgs::String &msg) {
	std::cout << "Message received: " << msg.data << std::endl;
	std_msgs::String ros_str;
	ros_str.data = "It's works!";
	return ros_str;
}


