#pragma once

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
namespace laser_scan {

/*!
 *
 */
class LaserScan {
public:
	/*!
	 * Constructor.
	 */
	LaserScan(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~LaserScan();

private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber_;
	void topicCallback(const sensor_msgs::PointCloud2::ConstPtr &msg);


};

} /* namespace */
