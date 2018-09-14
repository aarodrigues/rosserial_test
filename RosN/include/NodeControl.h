#pragma once

#include "ros.h"
#include <string>
#include "std_msgs/String.h"

class NodeControl
{
public:
	NodeControl(char *master_ip);
	~NodeControl();
	void initRosMaster();
	ros::NodeHandle m_nh;
	void listener();
	std_msgs::String callback(const std_msgs::String & msg);
	bool synch;
	bool ack;
private:
	//char ros_master[] = "10.88.28.14";
	char *m_ros_master;
	std_msgs::String acknowledging;
};

