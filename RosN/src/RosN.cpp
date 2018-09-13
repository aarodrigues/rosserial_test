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

ros::Publisher *cmd;
bool test = true;

void publishing(std::string msg, std::string topic_name) {

	std_msgs::String feedback;
	feedback.data = msg.c_str();
	ros::Publisher cmd_vel_pub("cmd_vel", &feedback);
	cmd = &cmd_vel_pub;
	control->m_nh.advertise(cmd_vel_pub);
	cmd_vel_pub.publish(&feedback);
	Sleep(5000);
	control->m_nh.spinOnce();
	/*for (int i = 0; i < 5; i++) {
	printf("Publishing  ...!\n");
	cmd_vel_pub.publish(&feedback);
	control->m_nh.spinOnce();
	}*/
	printf("Finish!\n");
	
}

void pose_callback(const std_msgs::String & msg)
{
	if(test){
		test = false;
		printf("pose_callback arrived!\n");
		printf("msg received %s\n", msg.data);
		std_msgs::String feedback = control->callback(msg);
		//publishing("connected", "cmd_vel");
	}
	
}

void loop() {
	publishing("connected", "cmd_vel");
	std_msgs::String feedback;
	feedback.data = "coisando";
	while (true)
	{
		std::cout << "Test value: " << test << std::endl;
		if (!test) {
			cmd->publish(&feedback);
			std::cout << "cheguei aqui" << std::endl;
		}
		control->m_nh.spinOnce();
		Sleep(100);
	}
}

int main()
{
	char ros_master[] = "10.88.28.8";

	/*NodeControl nc(ros_master);
	nc.initRosMaster();*/

	control = std::unique_ptr<NodeControl>(new NodeControl(ros_master));
	control->initRosMaster();

	//publishing("connected", "cmd_vel");
	

	ros::Subscriber<std_msgs::String> cmd_sub("chatter", &pose_callback);
	control->m_nh.subscribe(cmd_sub);

	/*publishing("connected", "cmd_vel");*/
	loop();
	printf("Go robot go!\n");
	//control->listener();
	getchar();

	return 0;
}