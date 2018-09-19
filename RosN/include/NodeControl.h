#pragma once

#include "ros.h"
#include <string>
#include "std_msgs/String.h"
#include "HySpexControl.h"

class NodeControl
{
public:
	NodeControl(char *master_ip);
	~NodeControl();
	void initRosMaster();
	ros::NodeHandle nh_;
	void listener();
	std_msgs::String callback(const std_msgs::String & msg);
	bool synch_;
	bool ack_;
	std::unique_ptr<HySpexControl> hyspex_control_;

private:
	//char ros_master[] = "10.88.28.14";
	char *m_ros_master;
	std_msgs::String acknowledging_;
	std_msgs::String status_;
	std_msgs::String angles_;

	bool enable_angle_;
	bool enable_status_;
	bool enable_perpetual_publishing_;

};

