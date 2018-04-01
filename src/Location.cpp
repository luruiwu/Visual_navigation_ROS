/***********************************************************************/
/*                           Location.cpp                              */
/***********************************************************************/
/* -VERSION: ROS_Ubuntu 14.04                                          */
/* -AUTHOR:  GUILLAUME Sylvain                                         */
/* -LAST_MODIFICATION: 03/2018                                         */
/***********************************************************************/


#include "Location.hpp"


// Constructor
Location::Location(ros::NodeHandle nh) 
{
  vo_subscriber_ = nh.subscribe("/vo", 1, &Location::vo_Callback, this);
  odom_publisher_ = nh.advertise<nav_msgs::Odometry>("/odom", 1);
  msg_ok_ = false;
}


// Callback of the ar_pose_marker topic. Sets the position of the amer
void Location::vo_Callback(nav_msgs::Odometry msg)
{
  if (!msg_ok_) 
  {
    odom_msg_ = msg;
    msg_ok_ = true;
  }
}

void Location::relocation()
{
  while(msg_ok_ == false && ros::ok())
  {
    ros::spinOnce();
    ros::Duration(0.05).sleep();
  }
  odom_publisher_.publish(odom_msg_);
  msg_ok_ == false;
}

