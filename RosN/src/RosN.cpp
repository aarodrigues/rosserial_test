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
#include "std_msgs/Bool.h"

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sstream>

#include "NodeControl.h"

#include <iostream>

std::unique_ptr<NodeControl> control;

//angle_pantilt
//confirm_start_hyspex
//start_hyspex
//geo_diagnostic

void ratified_connection(const std_msgs::String & msg) {
	printf("Parando: %s\n", msg.data);
	control->ack = true;
}


void synchronize(const std_msgs::String & msg)
{
	if(!control->synch){
		control->synch = true;
		printf("pose_callback arrived!\n");
		printf("msg received %s\n", msg.data);
	}
}

void publish_pool() {

	std_msgs::String log;
	log.data = "Log from HySpex";
	ros::Publisher log_pub("hyspex_log", &log);
	control->m_nh.advertise(log_pub);

	std_msgs::String angles;
	angles.data = "Log from HySpex";
	ros::Publisher pantilt_pub("pan_tilt", &angles);
	control->m_nh.advertise(pantilt_pub);
}


int main()
{
	char ros_master[] = "10.88.28.8";

	control = std::unique_ptr<NodeControl>(new NodeControl(ros_master));
	control->initRosMaster();
	
	ros::Subscriber<std_msgs::String> cmd_sub("chatter", &synchronize);
	control->m_nh.subscribe(cmd_sub);

	ros::Subscriber<std_msgs::String> confirm("second", &ratified_connection);
	control->m_nh.subscribe(confirm);

	printf("Go robot go!\n");
	control->listener();
	getchar();

	return 0;
}