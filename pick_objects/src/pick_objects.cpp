#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Int32.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

// Status: 0 = will pick up, 1 = picked up, 2 = dropped off
std_msgs::Int32 status;

int main(int argc, char** argv){
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Rate r(1);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  ros::Publisher status_pub = n.advertise<std_msgs::Int32>("robot_status", 1);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  float goal_points[2][2] = {{11.0, -5.0}, {13.0, 0.0}};

  goal.target_pose.pose.orientation.w = 1.0;
  
  status.data = 0;
  status_pub.publish(status);

  for (int i = 0; i < 2; i++){
    goal.target_pose.pose.position.x = goal_points[i][0];
    goal.target_pose.pose.position.y = goal_points[i][1];

    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if (i == 0){
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        status.data = 1;
        ROS_INFO("Hooray, the base moved to the pick up point");
      }
      else
        ROS_INFO("The base failed to move to the pick up point for some reason");
    }
    else{
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        status.data = 2;
        ROS_INFO("Hooray, the base moved to the drop off point");
      }
      else
        ROS_INFO("The base failed to move to the drop off point for some reason");
    }

    status_pub.publish(status);
    ros::Duration(5.0).sleep();
  }

  return 0;
}
