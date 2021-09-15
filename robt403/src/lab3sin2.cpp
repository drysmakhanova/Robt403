#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>

int main(int argc, char **argv){
  ros::init(argc, argv, "lab3sin2");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);
  ros::Rate loop_rate(50);

  float i = 0.0;
  while (ros::ok()){

  	std_msgs::Float64 sin_msg;
  	sin_msg.data = sin(i);
  	pub.publish(sin_msg);
  	ros::spinOnce();
  	loop_rate.sleep();
  	i = i+0.01;
 }
}
