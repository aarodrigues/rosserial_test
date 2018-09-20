#pragma once

#include "ros.h"
#include <string>
#include "std_msgs/String.h"
#include "HySpexControl.h"

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class NodeControl
{
public:
	NodeControl();
	~NodeControl();
	void initRosMaster();
	void listener();
	std_msgs::String callback(const std_msgs::String & msg);
	bool jsonConfig(json &jconfig);
	bool loadParameters();

	ros::NodeHandle nh_;
	bool synch_;
	bool ack_;
	std::unique_ptr<HySpexControl> hyspex_control_;

	std::string start_topic_;
	std::string angles_pantilt_topic_;
	std::string confirm_start_topic_;
	std::string second_confirmation_topic_;
	std::string status_topic_;
	std::string command_topic_;

private:
	char *ros_master_;
	std::string ros_ip_;
	std_msgs::String acknowledging_;
	std_msgs::String log_;
	std_msgs::String angles_;

	bool enable_angle_;
	bool enable_status_;
	bool enable_publishing_;

	std::string start_cmd_;

};

