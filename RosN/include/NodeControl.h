/**
 * @file	include\NodeControl.h.
 *
 * @brief	Function prototypes to NodeControl class structures.
 * 
 * NodeControl is responsable for manage the communication with ROS master on Linux through topics.
 * 
 * @author Alano Acioli.
 * @date Sep 2018.
 */

#pragma once

#include "ros.h"
#include <string>
#include "std_msgs/String.h"
#include "HySpexControl.h"

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class NodeControl
{
public:

	/**
	 * @fn	NodeControl::NodeControl();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Alano Acioli
	 * @date	20/09/2018
	 */

	NodeControl();

	/**
	 * @fn	NodeControl::~NodeControl();
	 *
	 * @brief	Destructor
	 *
	 * @author	Alano Acioli
	 * @date	20/09/2018
	 */

	~NodeControl();

	/**
	 * @fn	void NodeControl::listener();
	 *
	 * @brief	Listeners this object
	 *
	 * @author	Alano Acioli
	 * @date	20/09/2018
	 */

	void listener();

	/**
	 * @fn	std_msgs::String NodeControl::callback(const std_msgs::String & msg);
	 *
	 * @brief	Callbacks the given message
	 *
	 * @author	Alano Acioli
	 * @date	20/09/2018
	 *
	 * @param	msg	The message.
	 *
	 * @return	A std_msgs::String.
	 */

	std_msgs::String callback(const std_msgs::String & msg);


	/** @brief	ROS nodeHandle */
	ros::NodeHandle nh_;

	/** @brief	True to synchronise */
	bool synch_;

	/** @brief	True to acknowledge */
	bool ack_;

	/** @brief	Interface object to access commands from Hyspex application */
	std::unique_ptr<HySpexControl> hyspex_control_;
	
	/** @brief	ROS topics */
	std::string start_topic_;
	std::string angles_pantilt_topic_;
	std::string confirm_start_topic_;
	std::string second_confirmation_topic_;
	std::string status_topic_;
	std::string command_topic_;

private:

	/**
	 * @fn	void NodeControl::initRosMaster();
	 *
	 * @brief	Initializes the ros master
	 *
	 * @author	Alano Acioli
	 * @date	20/09/2018
	 */

	void initRosMaster();

	/**
	 * @fn	bool NodeControl::jsonConfig(json &jconfig);
	 *
	 * @brief	JSON configuration
	 *
	 * @author	Alano Acioli
	 * @date	20/09/2018
	 *
	 * @param [in,out]	jconfig	The jconfig.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */

	bool jsonConfig(json &jconfig);

	/**
	 * @fn	bool NodeControl::loadParameters();
	 *
	 * @brief	Loads the parameters from config.json
	 *
	 * @author	Alano Acioli
	 * @date	20/09/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 */

	bool loadParameters();


	/** @brief	The ros master ip address */
	char *ros_master_;


	/** @brief ros IP string */
	std::string ros_ip_;


	/** @brief	ROS messages */
	std_msgs::String acknowledging_;
	std_msgs::String log_;
	std_msgs::String angles_;


	/** @brief	Publishing controllers */
	bool enable_angle_;
	bool enable_status_;
	bool enable_publishing_;


	/** @brief	Commands from ROS topic */
	std::string start_cmd_;
	std::string move_pitch_cmd_;
	std::string move_yaw_cmd_;
	std::string detect_cam_cmd_;
	std::string detect_stages_cmd_;
	std::string stop_cmd_;
	std::string show_frame_acquisition_cmd_;
	std::string show_pantilt_pos_cmd_;
	std::string show_cam_id_cmd_;
	std::string set_sweep_angle_cmd_;
	std::string set_initial_pos_cmd_;
	std::string set_overlay_percent_cmd_;
	std::string set_scan_number_lines_cmd_;
	std::string set_integration_time_cmd_;
	std::string set_frame_period_cmd_;
	std::string set_return_speed_cmd_;
	std::string set_primary_cam_cmd_;

};

