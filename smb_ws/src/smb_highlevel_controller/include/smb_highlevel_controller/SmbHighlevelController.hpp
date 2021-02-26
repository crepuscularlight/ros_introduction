#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
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

	/*!
	 * Destructor.
	 */
	virtual ~SmbHighlevelController();

private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber_;
	void topicCallback(const sensor_msgs::LaserScan::ConstPtr &msg);


};

} /* namespace */
