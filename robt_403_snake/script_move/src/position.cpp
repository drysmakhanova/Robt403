#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <script_move/pose_joint.h>

class Listener {
	public:
	float posex;
	float posey;
	float joints[5];
	void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
	{
  	posex = msg->pose.position.x;
  	posey = msg->pose.position.y;
  	}
	void jointCallback(const sensor_msgs::JointState::ConstPtr& msg)
	{
  	for (int i=0; i<5; i++){
		joints[i] = msg->position[i];
  	}  	
  	}
	
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "position");
  ros::NodeHandle n;
  script_move::pose_joint data;

  Listener listener;
  
  ros::Subscriber sub = n.subscribe("Pose_endeff", 1000, &Listener::poseCallback, &listener);
  ros::Subscriber sub2 = n.subscribe("robot/joint_states", 1000, &Listener::jointCallback, &listener);
  
  ros::Publisher pose_pub = n.advertise<script_move::pose_joint>("Pose_endeff", 1000);
  
  ros::Rate loop_rate(500); //Frequency
  
  while (ros::ok()){
  	for (int i=0; i<5; i++){
		data.joint_states[i] = listener.joints[i];
  	}
  	data.position_x = listener.posex;
  	data.position_y = listener.posey;
    	pose_pub.publish(data);
 	ros::spinOnce();
    	loop_rate.sleep();
    	

  }

  ROS_INFO("Done");
  return 0;
}
