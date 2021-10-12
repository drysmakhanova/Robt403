#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>


// Main moveit libraries are included
int main(int argc, char **argv)
{
  ros::init(argc, argv, "triangle");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(0);
  spinner.start(); 
  
  static const std::string PLANNING_GROUP = "snake_arm"; 
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP); // loading move_group

  const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP); //For joint control
  geometry_msgs::PoseStamped current_pose;
  geometry_msgs::PoseStamped target_pose; 
  
  current_pose = move_group.getCurrentPose(); /* Retrieving the information about the current position and orientation of the end effector*/
  target_pose = current_pose;
 
  // Triangle move
  float length = 0.5;
  float width = 0.5;
  int count = 0;
  
  ros::Publisher pose_pub = node_handle.advertise<geometry_msgs::PoseStamped>("Pose_endeff", 1000);
 	
  ros::Rate loop_rate(500); //Frequency
  
  while (ros::ok()){
    pose_pub.publish(current_pose);
    if (count == 0) {
	// Getting into start position
 	target_pose.pose.position.x = target_pose.pose.position.x - 0.25; 
 	ROS_INFO("Start position");
    } else if (count == 1) {
    	ROS_INFO("y-dir1");
    	target_pose.pose.position.y = target_pose.pose.position.y + length; 
    } else if (count == 2) {
    	ROS_INFO("x-dir1");
    	target_pose.pose.position.x = target_pose.pose.position.x - width; 
    } else if (count == 3) {
    	ROS_INFO("hypo");
    	target_pose.pose.position.x = target_pose.pose.position.x + width; 
    	target_pose.pose.position.y = target_pose.pose.position.y - length;     
    } else {
    	count = 0;
    }

    count = count + 1;
    
    move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
    move_group.move(); // Move the robot
    current_pose = move_group.getCurrentPose();
    
    if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.1 && abs(current_pose.pose.position.y - target_pose.pose.position.y) < 0.1){
      	continue; // Basically, check if we reached the desired position
    } else {
    	ROS_INFO("Current x: %f", current_pose.pose.position.x);
    	ROS_INFO("Target x: %f", target_pose.pose.position.x);
    	ROS_INFO("Current y: %f", current_pose.pose.position.y);
    	ROS_INFO("Target y: %f", target_pose.pose.position.y);
    	ROS_INFO("Error");
  	ros::shutdown();
    }
    loop_rate.sleep();

  }

  ROS_INFO("Done");
  ros::shutdown();
  return 0;
}
