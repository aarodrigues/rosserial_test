#pragma once

#include "ros.h"
#include <string>
#include "std_msgs/String.h"

class NodeControl
{
public:
	NodeControl(char *master_ip);
	~NodeControl();
	void initRMaster();
	ros::NodeHandle m_nh;
	void subscriber();
	void listener();
	void callback(const std_msgs::String & msg);
private:
	//char ros_master[] = "10.88.28.14";
	char *m_ros_master;
};

