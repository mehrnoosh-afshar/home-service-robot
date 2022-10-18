# home-service-robot
 The mission of the robot is picking an object and bring it to the goal. First, the robot moves to the pick up point. There is a  sphere on the pick up point. This sherre represents the object that will be pick up. When robot reached the pick up point, it picks up the object and the marker disappears. Then, robot moves to the drop off point.
 When it reached the drop off point, it drops off the object and the sphere appers on the drop off point.
 
 
Running the Project
You need to clone this repo in a catkin_ws and change its name to the src. Write catkin_make in the root directory of catkin_ws to compile it. Write source devel/setup.bash after compiled. To install dependencies of packages write below commands.

$ rosdep -i install gmapping

$ rosdep -i install turtlebot_teleop

$ rosdep -i install turtlebot_rviz_launchers

$ rosdep -i install turtlebot_gazebo



# Packages
There are six packages in the project. The four of them are previously written packages. These packages are gmapping, turtlebot, turtlebot_interactions, and turtlebot_simulator. slam_gmapping package is for SLAM operations. turtlebot package is used to control robot with teleop keys. turtlebot_interactions package is for rviz launcher. turtlebot_simulator package is for Gazebo simulator launcher.

two packages are written which are  are pick_objects and add_markers.

# Supporting Packages
First, there are four supporting packages to install for the project.

slam_gmapping provides SLAM capability in conjunction with the gmapping package. The gmapping package provides laser-based SLAM, as a ROS node called slam_gmapping. Using slam_gmapping, you can create a 2-D occupancy grid map from laser and pose data collected by a mobile robot. 
The slam_gmapping node takes in sensor_msgs/LaserScan messages and builds a map (nav_msgs/OccupancyGrid).






turtlebot provides underlying drivers and specifications for the Turtlebot 2 in ROS Kinetic, and also keyboard control functionality for this project.
turtlebot_interactions provides the RViz launcher scripts.
turtlebot_simulator connects the Turtlebot packages with the Gazebo environment.

# Test_Slam 
The test_slam.sh script simply launches Gazebo with the home environment, places a turtlebot in it and launches the slam_gmapping nodes. The user can move the robot in the environment using keyboard as in turtlebot_teleop. Run this script to verify that the packages and dependencies have been installed correctly.

# Test Navigation
The tesst_navigation.sh script builds on top of the test_slam.sh script and enables the robot to reach a goal pose designated by the user in RViz through the amcl package.


# Pick Objects
pick_objects package includes pick_objects node. It sends pick up and drop off points to the move_base action server. 

# Add Markers
add_markers package includes add_markers node. It publishes to visualization_marker to draw a white sphere which represents the object. It subscribes to ACML pose topic to get the robot pose in map framework from tpic publishing from ACML package. If the robot didn't pick up the object yet, it draws it on the pick up point. If robot picked up the object, it deletes object. If the robot reached to the goal point and dropped off the object, it draws it on the drop off point.
