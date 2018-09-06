// RosN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "ros.h"
#include <geometry_msgs/Twist.h>
#include <windows.h>

#include "std_msgs/String.h"

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sstream>

#include "NodeControl.h"

bool stop = false;

void pose_callback(const std_msgs::String & msg)
{
	printf("msg received %s\n", msg.data);
}

int main()
{
	char ros_master[] = "10.88.28.14";

	NodeControl nc(ros_master);
	nc.initRMaster();

	//ros::Subscriber<std_msgs::String> cmd_sub("chatter", 1000, &NodeControl::callback, &nc);
	ros::Subscriber<std_msgs::String> cmd_sub("chatter", &pose_callback);
	nc.m_nh.subscribe(cmd_sub);
	printf("Go robot go!\n");
	nc.listener();
	getchar();

	return 0;
}