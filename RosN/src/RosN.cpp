// RosN.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "ros.h"
#include <windows.h>

#include "NodeControl.h"
#include "HySpex.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

std::unique_ptr<NodeControl> control;

void execute_command(const std_msgs::String & msg) {
	printf("Execute: %s\n", msg.data);
	control->callback(msg);
}

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
	control = std::unique_ptr<NodeControl>(new NodeControl());

	ros::Subscriber<std_msgs::String> cmd_sub(control->start_topic_.c_str(), &synchronize);
	control->nh_.subscribe(cmd_sub);

	ros::Subscriber<std_msgs::String> confirm(control->second_confirmation_topic_.c_str(), &ratified_connection);
	control->nh_.subscribe(confirm);

	ros::Subscriber<std_msgs::String> command(control->command_topic_.c_str(), &execute_command);
	control->nh_.subscribe(command);

	printf("Go robot go!\n");
	control->listener();
	
	getchar();

	return 0;
}