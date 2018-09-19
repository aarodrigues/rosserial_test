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

const char *ANGLES_PANTILT = "/qm_hyspex_controller/angles_pantilt";
const char *CONFIRM_START = "/qm_hyspex_controller/confirm_start_hyspex";
const char *START = "/qm_hyspex_controller/start_hyspex";
const char *SECOND_CONFIRMATION = "/qm_hyspex_controller/2step_confirmation_start_hyspex";
const char *STATUS = "/qm_hyspex_controller/checking_status_hyspex";


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

	ros::Subscriber<std_msgs::String> cmd_sub(START, &synchronize);
	control->nh_.subscribe(cmd_sub);

	ros::Subscriber<std_msgs::String> confirm(SECOND_CONFIRMATION, &ratified_connection);
	control->nh_.subscribe(confirm);

	printf("Go robot go!\n");
	control->listener();
	
	getchar();

	return 0;
}