#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Vector3.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <math.h>


float poseAMCLx = 0.0, poseAMCLy = 0.0 , poseAMCLa = 0.0;
void poseAMCLCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msgAMCL)
{
    ::poseAMCLx = msgAMCL->pose.pose.position.x;
    ::poseAMCLy = msgAMCL->pose.pose.position.y;
    ::poseAMCLa = msgAMCL->pose.pose.orientation.w;   
}




int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(20);
  ros::Subscriber sub_amcl = n.subscribe("amcl_pose", 1000, poseAMCLCallback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::SPHERE;

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;
  float dx, dy;

  float eps = 0.15;
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = 11.0;
  marker.pose.position.y = 5.0;
  marker.pose.orientation.w = 1.0;


  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 1.0f;
  marker.color.g = 1.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  while (ros::ok())
  {


    // Publish the marker
   
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    





    ROS_INFO("ACML data: %f, %f", poseAMCLx, poseAMCLy);


    marker_pub.publish(marker);
    dx = fabs(marker.pose.position.x - poseAMCLx);
    dy = fabs(marker.pose.position.y - poseAMCLy);

    if( (dx < eps) && (dy < eps) ){
          marker.action = visualization_msgs::Marker::DELETE;
          marker_pub.publish(marker);}
 
     dx = fabs(13.5 - poseAMCLx);
     dy = fabs(-6.0 - poseAMCLy);

     if( (dx < eps) && (dy < eps) ){
          marker.action = visualization_msgs::Marker::ADD;
          marker.pose.position.x = 13.5;
          marker.pose.position.y = -6.0;
          marker_pub.publish(marker);}
      

    ros::spinOnce();
    r.sleep();

    }
    return 0;
}




