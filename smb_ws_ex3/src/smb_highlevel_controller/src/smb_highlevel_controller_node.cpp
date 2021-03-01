#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"
#include <sensor_msgs/LaserScan.h>
#include<string>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "smb_highlevel_controller");
	ros::NodeHandle nodeHandle;




	 smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

	 /*ros::Subscriber subscriber = nodeHandle.subscribe(topic, queue_size, scanCallback);*/
	 ros::spin();
	 return 0;
}
