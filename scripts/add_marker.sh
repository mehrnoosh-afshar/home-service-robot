#!/bin/sh
xterm  -e  " export ROBOT_INITIAL_POSE='-x 5 -y 5'; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch" & 
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm  -e  " rosrun add_markers test_markers "
