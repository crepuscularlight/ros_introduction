#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include<sensor_msgs/PointCloud2.h>
namespace smb_highlevel_controller {

/*!
 *
 */
class SmbHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	SmbHighlevelController(ros::NodeHandle& nodeHandle);
	SmbHighlevelController(ros::NodeHandle& nodeHandle,int x);
	/*!
	 * Destructor.
	 */
	virtual ~SmbHighlevelController();

private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber_;
	void topicCallback(const sensor_msgs::LaserScan::ConstPtr &msg);
	void topicCallback1(const sensor_msgs::PointCloud2::ConstPtr &msg);


};

} /* namespace */
