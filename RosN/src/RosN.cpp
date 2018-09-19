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
#include "HySpex.h"

#include <iostream>

std::unique_ptr<NodeControl> control;

void ratified_connection(const std_msgs::String & msg) {
	printf("Parando: %s\n", msg.data);
	control->ack_ = true;
}


void synchronize(const std_msgs::String & msg)
{
	if(!control->synch_){
		control->synch_ = true;
		printf("pose_callback arrived!\n");
		printf("msg received %s\n", msg.data);
	}
}

int main()
{
	char ros_master[] = "10.88.28.8";

	control = std::unique_ptr<NodeControl>(new NodeControl(ros_master));
	control->initRosMaster();

	ros::Subscriber<std_msgs::String> cmd_sub(control->START, &synchronize);
	control->nh_.subscribe(cmd_sub);

	ros::Subscriber<std_msgs::String> confirm(control->SECOND_CONFIRMATION, &ratified_connection);
	control->nh_.subscribe(confirm);

	printf("Go robot go!\n");
	control->listener();
	
	getchar();

	return 0;
}