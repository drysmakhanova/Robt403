#include <ros/ros.h>
#include <std_msgs/Float64.h>


int main(int argc, char **argv){
  ros::init(argc, argv, "lab3step2");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);
  ros::Rate loop_rate(1);

  int count = 0;
  while (ros::ok()){

  	std_msgs::Float64 step1;
  	step1.data = 0.0;
  	std_msgs::Float64 step2;
  	step2.data = 1.0;
  	if (count%4 == 0) 
  	{
  	pub.publish(step2);
  	}
	else if (count%4 == 2)
  	{
  	pub.publish(step1);
  	}
  	count++;
  	ros::spinOnce();
  	loop_rate.sleep();
 }
}
