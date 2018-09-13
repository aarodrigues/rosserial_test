#include "NodeControl.h"
#include<iostream>
#include <windows.h>

NodeControl::NodeControl(char *master_ip): m_ros_master(master_ip)
{
}


NodeControl::~NodeControl()
{
}

//
//void NodeControl::initRosMaster() {
//	std::cout << "Connecting to server at " << m_ros_master << std::endl;
//	m_nh.initNode(m_ros_master);
//}
//
//void NodeControl::listener() {
//	while (true)
//	{
//		m_nh.spinOnce();
//		Sleep(100);
//	}
//}
//
//std_msgs::String NodeControl::callback(const std_msgs::String &msg) {
//	std::cout << "Message received: " << msg.data << std::endl;
//	std_msgs::String ros_str;
//	ros_str.data = "It's works!";
//	return ros_str;
//}