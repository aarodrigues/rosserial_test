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
ros::NodeHandle nodeHandle;
std_msgs::String feedback;
bool confirmed = false;

void stop_confirmation(const std_msgs::String & msg) {
	printf("Parando: %s\n", msg.data);
	confirmed = true;
}

void publishing(std::string msg, std::string topic_name) {

	//std_msgs::String feedback;
	feedback.data = msg.c_str();
	ros::Publisher cmd_vel_pub(topic_name.c_str(), &feedback);
	nodeHandle.advertise(cmd_vel_pub);
	cmd = &cmd_vel_pub;
	printf("Finish!\n");
	
}

void pose_callback(const std_msgs::String & msg)
{
	if(test){
		test = false;
		printf("pose_callback arrived!\n");
		printf("msg received %s\n", msg.data);
		//std_msgs::String feedback = control->callback(msg);
		//publishing("connected", "cmd_vel");
	}
	
}

void loop() {
	//publishing("connected", "cmd_vel");
	std_msgs::String feedback;
	feedback.data = "coisando";
	ros::Publisher cmd_vel_pub("cmd_vel", &feedback);
	nodeHandle.advertise(cmd_vel_pub);

	while (true)
	{
		//std::cout << "Test value: " << test << std::endl;
		if (!test) {
			if(!confirmed)
				cmd_vel_pub.publish(&feedback);
			//cmd->publish(&feedback);
			//std::cout << "cheguei aqui" << std::endl;
		}
		nodeHandle.spinOnce();
		Sleep(100);
	}
}

int main()
{
	char ros_master[] = "10.88.28.8";

	/*NodeControl nc(ros_master);
	nc.initRosMaster();*/

	control = std::unique_ptr<NodeControl>(new NodeControl(ros_master));
	//control->initRosMaster();

	nodeHandle.initNode(ros_master);
	//publishing("connected", "cmd_vel");
	

	ros::Subscriber<std_msgs::String> cmd_sub("chatter", &pose_callback);
	nodeHandle.subscribe(cmd_sub);

	ros::Subscriber<std_msgs::String> confirm("second", &stop_confirmation);
	nodeHandle.subscribe(confirm);

	/*publishing("connected", "cmd_vel");*/
	loop();
	printf("Go robot go!\n");
	//control->listener();
	getchar();

	return 0;
}