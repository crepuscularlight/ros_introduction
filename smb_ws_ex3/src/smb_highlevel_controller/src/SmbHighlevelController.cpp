#include "smb_highlevel_controller/SmbHighlevelController.hpp"

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle):nodeHandle_(nodeHandle)
{
	  std::string topic;
	  int queue_size;

	  if(!nodeHandle.getParam("smb_highlevel_controller/topic", topic)) {
	    ROS_ERROR("Could not find topic parameter!");
	  }

	  if (!nodeHandle.getParam("smb_highlevel_controller/queue_size", queue_size)) {
	    ROS_ERROR("Could not find queue_size parameter!");
	  }

	  if (!nodeHandle.getParam("smb_highlevel_controller/p_gain", p_gain)) {
	      ROS_ERROR("Could not find p_gain parameter!");
	    }

	   if (!nodeHandle.getParam("smb_highlevel_controller/x_dot", x_dot)) {
	        ROS_ERROR("Could not find x_dot parameter!");
	    }


	  subscriber_ = nodeHandle.subscribe(topic, queue_size, &SmbHighlevelController::topicCallback,this);
	  publisher_ = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

	  vis_pub_ = nodeHandle.advertise<visualization_msgs::Marker>("/visualization_marker", 0);

}

SmbHighlevelController::~SmbHighlevelController()
{
}

void SmbHighlevelController::topicCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
	  int i = 0;
	  int size = msg->ranges.size();

	  float min_dis = msg->range_max;
	  float min_i = 0;

	  // get min distance
	  for (i = 0; i < size; i++)
	  {
	    float dist = msg->ranges.at(i);

	    if (dist < min_dis) {
	      min_dis = dist;
	      min_i = i;
	    }
	  }

	  float angle_increment = msg->angle_increment;
	  float angle_min = msg->angle_min;
	  float rad = angle_min + angle_increment * min_i;

	  float x, y, z;

	  x = min_dis * cos(rad);
	  y = min_dis * sin(rad);
	  z = 0;

	  ROS_INFO("x: %f \ny: %f", x, y);

	  float angle_dot, x_dot;

	  angle_dot = SmbHighlevelController::p_gain * (0 + rad);
	  x_dot = SmbHighlevelController::x_dot;


	    // publish control input as message
	    geometry_msgs::Twist base_cmd;
	    base_cmd.linear.x = x_dot;
	    base_cmd.angular.z = angle_dot;

	    publisher_.publish(base_cmd);

	    // publish visualization marker
	    visualization_msgs::Marker marker;
	    marker.header.frame_id = "base_link";
	    marker.header.stamp = ros::Time();
	    marker.ns = "my_namespace";
	    marker.id = 0;
	    marker.type = visualization_msgs::Marker::CYLINDER;
	    marker.action = visualization_msgs::Marker::ADD;
	    marker.pose.position.x = x;
	    marker.pose.position.y = y;
	    marker.pose.position.z = z;
	    marker.pose.orientation.x = 0.0;
	    marker.pose.orientation.y = 0.0;
	    marker.pose.orientation.z = 0.0;
	    marker.pose.orientation.w = 1.0;
	    marker.scale.x = 1;
	    marker.scale.y = 1;
	    marker.scale.z = 1;
	    marker.color.a = 1.0; // Don't forget to set the alpha!
	    marker.color.r = 1.0;
	    marker.color.g = 1.0;
	    marker.color.b = 0.0;
	    //only if using a MESH_RESOURCE marker type:
	    marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
	    vis_pub_.publish(marker);

}

} /* namespace */
