#include <ros/ros.h>
#include <std_msgs/Float64.h>


int main(int argc, char **argv){
  ros::init(argc, argv, "lab3step");
  ros::NodeHandle nh1;
  ros::NodeHandle nh2;

  ros::Publisher pub1 = nh1.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 100);
  ros::Publisher pub2 = nh2.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);
  ros::Rate loop_rate(1);

  int count = 0;
  while (ros::ok()){

  	std_msgs::Float64 step1;
  	step1.data = 0.0;
  	std_msgs::Float64 step2;
  	step2.data = 1.0;
  	if (count%4 == 0) 
  	{
  	pub1.publish(step2);
  	}
  	else if (count%4 == 1) 
  	{
  	pub2.publish(step2);
  	}
  	else if (count%4 == 2) 
  	{
  	pub1.publish(step1);
  	}
	else 
  	{
  	pub2.publish(step1);
  	}
  	count++;
  	ros::spinOnce();
 }
}
