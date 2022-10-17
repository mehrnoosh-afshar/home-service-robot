#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Vector3.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <math.h>


double poseAMCLx, poseAMCLy, poseAMCLa;
void poseAMCLCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msgAMCL)
{
    poseAMCLx = msgAMCL->pose.pose.position.x;
    poseAMCLy = msgAMCL->pose.pose.position.y;
    poseAMCLa = msgAMCL->pose.pose.orientation.w;   
}



int main( int argc, char** argv )
   {
     ros::init(argc, argv, "add_markers");
     ros::NodeHandle n;
     ros::Rate r(1);
     ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
     ros::Subscriber sub_amcl = n.subscribe("amcl_pose", 1000, poseAMCLCallback);
    
     geometry_msgs::Vector3  first_target;
     geometry_msgs::Vector3  second_target;
     
     float eps = 0.15 ;
     float dx ,dy ;
    first_target.x = 11.0;
    first_target.y = -5.0;
    first_target.z = 1.0;

    second_target.x = 13.0;
    second_target.y = 0.0;
    second_target.z = 1.0;
  
    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::SPHERE;
   
     while (ros::ok())
     {
       ros::spinOnce();
       visualization_msgs::Marker marker;
       // Set the frame ID and timestamp.  See the TF tutorials for information on these.
       marker.header.frame_id = "map";
       marker.header.stamp = ros::Time::now();
   
       // Set the namespace and id for this marker.  This serves to create a unique ID
       // Any marker sent with the same namespace and id will overwrite the old one
       marker.ns = "add_markers";
       marker.id = 0;
   
       // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
       marker.type = shape;
   
       // Set the scale of the marker -- 1x1x1 here means 1m on a side
       marker.scale.x = 1.0;
       marker.scale.y = 1.0;
       marker.scale.z = 1.0;
   
       // Set the color -- be sure to set alpha to something non-zero!
       marker.color.r = 0.0f;
       marker.color.g = 1.0f;
       marker.color.b = 1.0f;
       marker.color.a = 1.0;
   
       marker.lifetime = ros::Duration();
       

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
        

       // Set the initial for the marker
       marker.pose.position.x = first_target.x;
       marker.pose.position.y = first_target.y;
       marker.pose.position.z = 0;
       marker.pose.orientation.x = 0.0;
       marker.pose.orientation.y = 0.0;
       marker.pose.orientation.z = 0.0;
       marker.pose.orientation.w = first_target.z;
       
       marker_pub.publish(marker);
       
       marker.action = visualization_msgs::Marker::ADD;
       dx = fabs(poseAMCLx- first_target.x);
       dy = fabs(poseAMCLy- first_target.y);
       
       
      
       if (dx < eps && dy < eps ){
               marker.action = visualization_msgs::Marker::DELETE;
               ros::Duration(5.0).sleep();
               marker_pub.publish(marker);
       }
       
       dx = fabs(poseAMCLx- second_target.x);
       dy = fabs(poseAMCLy- second_target.y);
       
       if (dx < eps && dy < eps){

          marker.pose.position.x = second_target.x;
          marker.pose.position.y = second_target.y;
          marker.action = visualization_msgs::Marker::ADD;
          marker_pub.publish(marker);
     
       }

  
       
      
      r.sleep();
      return 0;
    }
  }

