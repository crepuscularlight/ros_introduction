#include "smb_highlevel_controller/SmbHighlevelController.hpp"

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle):nodeHandle_(nodeHandle)
{
	  std::string topic;
	  int queue_size;

	 /* if(!nodeHandle.getParam("smb_highlevel_controller/topic", topic)) {
	    ROS_ERROR("Could not find topic parameter!");
	  }

	  if (!nodeHandle.getParam("smb_highlevel_controller/queue_size", queue_size)) {
	    ROS_ERROR("Could not find queue_size parameter!");
	  }*/

	  subscriber_ = nodeHandle.subscribe("/scan",10, &SmbHighlevelController::topicCallback,this);

}
SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle,int x):nodeHandle_(nodeHandle)
{


	  subscriber_ = nodeHandle.subscribe("rslidar_points", 10, &SmbHighlevelController::topicCallback1,this);

}

SmbHighlevelController::~SmbHighlevelController()
{
}

void SmbHighlevelController::topicCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
	float min_data=0;
	int length=msg->ranges.size();
	float temp=msg->range_max;
	for(int i=0;i<length;i++)
	{
		if(temp>msg->ranges[i])
			temp=msg->ranges[i];
	}
	min_data=temp;
	ROS_INFO("minimum range is %f",min_data);
}
void SmbHighlevelController::topicCallback1(const sensor_msgs::PointCloud2::ConstPtr &msg)
{
	ROS_INFO("point number is %d",msg->row_step*msg->height);
}

} /* namespace */
