#include "NodeControl.h"
#include<iostream>
#include <windows.h>

NodeControl::NodeControl(char *master_ip): m_ros_master(master_ip)
{
}


NodeControl::~NodeControl()
{
}


void NodeControl::initRMaster() {
	std::cout << "Connecting to server at " << m_ros_master << std::endl;
	m_nh.initNode(m_ros_master);
}

void NodeControl::subscriber() {
	/*ros::Subscriber<std_msgs::String> command_sub("chatter", &NodeControl::initRMaster);
	m_nh.subscribe(command_sub);*/
}

void NodeControl::listener() {
	while (true)
	{
		m_nh.spinOnce();
		Sleep(100);
	}
}

void NodeControl::callback(const std_msgs::String &msg) {
	std::cout << "Message received: " << msg.data << std::endl;
}