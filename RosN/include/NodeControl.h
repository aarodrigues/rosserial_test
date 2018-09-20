#pragma once

#include "ros.h"
#include <string>
#include "std_msgs/String.h"
#include "HySpexControl.h"

//namespace ros_topic {
//	const char *ANGLES_PANTILT = "/qm_hyspex_controller/angles_pantilt";
//	const char *CONFIRM_START = "/qm_hyspex_controller/confirm_start_hyspex";
//	const char *START = "/qm_hyspex_controller/start_hyspex";
//	const char *SECOND_CONFIRMATION = "/qm_hyspex_controller/2step_confirmation_start_hyspex";
//	const char *STATUS = "/qm_hyspex_controller/checking_status_hyspex";
//};

class NodeControl
{
public:
	NodeControl(char *master_ip);
	~NodeControl();
	void initRosMaster();
	void listener();
	std_msgs::String callback(const std_msgs::String & msg);

	ros::NodeHandle nh_;
	bool synch_;
	bool ack_;
	std::unique_ptr<HySpexControl> hyspex_control_;


	const char *ANGLES_PANTILT = "/qm_hyspex_controller/angles_pantilt";
	const char *CONFIRM_START = "/qm_hyspex_controller/confirm_start_hyspex";
	const char *START = "/qm_hyspex_controller/start_hyspex";
	const char *SECOND_CONFIRMATION = "/qm_hyspex_controller/2step_confirmation_start_hyspex";
	const char *STATUS = "/qm_hyspex_controller/checking_status_hyspex";
	const char *COMMAND = "/qm_hyspex_controller/qm_hyspex_command";

private:
	char *m_ros_master_;
	std_msgs::String acknowledging_;
	std_msgs::String status_;
	std_msgs::String angles_;

	bool enable_angle_;
	bool enable_status_;
	bool enable_publishing_;

};

