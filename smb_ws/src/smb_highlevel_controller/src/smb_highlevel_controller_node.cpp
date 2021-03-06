#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"
#include <sensor_msgs/LaserScan.h>
#include<string>

void scanCallback(const sensor_msgs::LaserScan & msg)
{

	float min_data=0;
	int length=msg.ranges.size();
	float temp=msg.range_max;
	for(int i=0;i<length;i++)
	{
		if(temp>msg.ranges[i])
			temp=msg.ranges[i];
	}
	min_data=temp;
	ROS_INFO("minimum range is %f",min_data);

}
int main(int argc, char** argv)
{
	ros::init(argc, argv, "smb_highlevel_controller");
	ros::NodeHandle nodeHandle;




	 smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

	 /*ros::Subscriber subscriber = nodeHandle.subscribe(topic, queue_size, scanCallback);*/
	 ros::spin();
	 return 0;
}
