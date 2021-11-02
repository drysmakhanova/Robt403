#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Received: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "lab1sub");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("rysmakhanova", 1000, chatterCallback);
  ros::spin();

  return 0;
}
