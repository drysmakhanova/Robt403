#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>


int main(int argc, char **argv)
{

  ros::init(argc, argv, "lab1pub");
  ros::NodeHandle n;
  ros::Publisher lab1_pub = n.advertise<std_msgs::String>("rysmakhanova", 1000);

  ros::Rate loop_rate(2);

  int count = 0;
  while (ros::ok())
  {

    std_msgs::String msg;

    std::stringstream ss;
    if (count%10 == 0){
    	ss << "ID: ";
    	}
    else if (count%10 == 1){
    	ss << "2";}
    else if (count%10 == 2){
    	ss << "0";}
    else if (count%10 == 3){
    	ss << "1";}
    else if (count%10 == 4){
    	ss << "4";}
    else if (count%10 == 5){
    	ss << "8";}
    else if (count%10 == 6){
    	ss << "6";}
    else if (count%10 == 7){
    	ss << "7";}
    else if (count%10 == 8){
    	ss << "1";}
    else if (count%10 == 9){
    	ss << "7";}

    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    lab1_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
