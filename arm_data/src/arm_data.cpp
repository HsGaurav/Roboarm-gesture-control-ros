#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include "iostream"
#include <fstream>
#include <std_msgs/Int8.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float64MultiArray.h"

using namespace std;



int main(int argc, char **argv)
{
	ros::init(argc, argv, "arm_data");

	ros::NodeHandle node;

	tf::TransformBroadcaster br;
	
	// ros::Publisher arm_data = node.advertise<std_msgs::Float64MultiArray>("arm_data", 10);
	// ros::Publisher arm_data = node.advertise<arm::Data>("arm_data", 10);

	tf::StampedTransform transform_shoulder_prev, transform_shoulder_curr, transform_elbow_prev, transform_elbow_curr, transform_shoulder_diff, transform_elbow_diff;

	tf::TransformListener listener;

	ros::Rate rate(2.0);

	if(node.ok()){
		try{
			listener.lookupTransform("/openni_depth_frame", "/right_shoulder_1", ros::Time(0), transform_shoulder_curr);
			listener.lookupTransform("/openni_depth_frame", "/right_shoulder_1", ros::Time(0), transform_shoulder_prev);
			listener.lookupTransform("/openni_depth_frame", "/right_elbow_1", ros::Time(0), transform_elbow_curr);
			listener.lookupTransform("/openni_depth_frame", "/right_elbow_1", ros::Time(0), transform_elbow_prev);
		}
	    catch (tf::TransformException ex){
	         ROS_ERROR("%s",ex.what());
	         // ros::Duration(1.0).sleep();
	    }
	}
	ros::NodeHandle nh;

	while (node.ok()){

	    try{
	    	listener.lookupTransform("/openni_depth_frame", "/right_shoulder_1", ros::Time(0), transform_shoulder_curr);
	    	listener.lookupTransform("/openni_depth_frame", "/right_elbow_1", ros::Time(0), transform_elbow_curr);
	    }
	    catch (tf::TransformException ex){
	         ROS_ERROR("%s",ex.what());
	         ros::Duration(1.0).sleep();
	    }

	    const tf::Quaternion &quaternion_shoulder_diff = transform_shoulder_curr.getRotation();
	    const tf::Quaternion &quaternion_elbow_diff = transform_elbow_curr.getRotation();
	    
	    double roll, pitch, yaw;


	    tf::Matrix3x3 m(quaternion_shoulder_diff);
	    m.getRPY(roll, pitch, yaw);
	    roll = roll * 57;
	    pitch = pitch * 57;
	    yaw = yaw * 57;		


	    ros::Publisher pub1 = nh.advertise<std_msgs::Int8>("S_roll", 1);
            std_msgs::Int8 Srol;
	    Srol.data = roll;
	    pub1.publish(Srol);

	    ros::Publisher pub2 = nh.advertise<std_msgs::Int8>("S_pitch", 1);
	    std_msgs::Int8 Spith;
	    Spith.data = pitch;
	    pub2.publish(Spith);

	    ros::Publisher pub3 = nh.advertise<std_msgs::Int8>("S_yaw", 1);
	    std_msgs::Int8 Syae;
	    Syae.data = yaw;
	    pub3.publish(Syae);

	    m = tf::Matrix3x3 (quaternion_elbow_diff);
	    m.getRPY(roll,pitch,yaw);

	    ros::Publisher pub4 = nh.advertise<std_msgs::Int8>("E_roll", 1);
	    std_msgs::Int8 Erol;
	    Erol.data = roll;
	    pub4.publish(Erol);

	    ros::Publisher pub5 = nh.advertise<std_msgs::Int8>("E_pitch", 1);
	    std_msgs::Int8 Epith;
	    Epith.data = pitch;
	    pub5.publish(Epith);

	    ros::Publisher pub6 = nh.advertise<std_msgs::Int8>("E_yaw", 1);
	    std_msgs::Int8 Eyae;
	    Eyae.data = yaw;
	    pub6.publish(Eyae);


	    rate.sleep();
	}

	return 0;
}
