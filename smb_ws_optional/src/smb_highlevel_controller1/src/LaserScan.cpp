#include "laser_scan/LaserScan.hpp"

namespace laser_scan {

LaserScan::LaserScan(ros::NodeHandle& nodeHandle):nodeHandle_(nodeHandle)
{
	  std::string topic;
	  int queue_size;

	  if(!nodeHandle.getParam("smb_highlevel_controller/laser_scan/topic", topic)) {
	    ROS_ERROR("Could not find topic parameter!");
	  }

	  if (!nodeHandle.getParam("smb_highlevel_controller/laser_scan/queue_size", queue_size)) {
	    ROS_ERROR("Could not find queue_size parameter!");
	  }

	  subscriber_ = nodeHandle.subscribe(topic, queue_size, &LaserScan::topicCallback,this);

}

LaserScan::~LaserScan()
{
}

void LaserScan::topicCallback(const sensor_msgs::PointCloud2::ConstPtr &msg)
{

	ROS_INFO("minimum range is %f",msg->row_step*msg->height);
}

} /* namespace */
