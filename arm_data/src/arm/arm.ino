#include <Servo.h>
#include <math.h>
#include <ros.h>
#include <std_msgs/Int8.h>
#define pi 3.141

using namespace std;

Servo servo[9];

//=====================================================================================================================================================================//
// angles.........0...0...90...90...0...0
// first preference is always given to right servo
//=====================================================================================================================================================================//
int a1 = 0; //wrist
int a2 = 80; //wrist
int a3 = 60; //elbow
int a4 = 90; //elbow
int a5 = 0; //shoulder
int a6 = 90; //base8

double s_roll, s_pitch, s_yaw;
double e_roll, e_pitch, e_yaw;
double base_v, base_h;

ros::NodeHandle nh;

void Sr( const std_msgs::Int8& toggle_msg){
  s_roll = toggle_msg.data;
}

void Sp( const std_msgs::Int8& toggle_msg){
  s_pitch = toggle_msg.data;
}


void Sy( const std_msgs::Int8& toggle_msg){
  s_yaw = toggle_msg.data;
}


void Er( const std_msgs::Int8& toggle_msg){
  e_roll = toggle_msg.data;
}


void Ep( const std_msgs::Int8& toggle_msg){
  e_pitch = toggle_msg.data;
}


void Ey( const std_msgs::Int8& toggle_msg){
  e_yaw = toggle_msg.data;
}


ros::Subscriber<std_msgs::Int8> sub1("S_roll", &Sr );

ros::Subscriber<std_msgs::Int8> sub2("S_pitch", &Sp );

ros::Subscriber<std_msgs::Int8> sub3("S_yaw", &Sy );

ros::Subscriber<std_msgs::Int8> sub4("E_roll", &Er );

ros::Subscriber<std_msgs::Int8> sub5("E_pitch", &Ep );

ros::Subscriber<std_msgs::Int8> sub6("E_yaw", &Ey );


void setup(){
  servo[0].attach(45);
  servo[1].attach(44);
  servo[2].attach(4);
  servo[3].attach(5);
  servo[4].attach(6);
  servo[5].attach(7);
  servo[6].attach(8);
  servo[7].attach(9);
  servo[8].attach(10);
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
  nh.subscribe(sub6);
}

void loop(){
  //s_roll = Serial.read();
  //s_pitch = Serial.read();
  //s_yaw = Serial.read();
  //e_roll = Serial.read();
  //e_pitch = Serial.read();
  //e_yaw = Serial.read();
  base_v = findAngle(s_roll,s_pitch);
  //Serial.println("Reading values");
  servo[0].write(a1);
  servo[1].write(a2);
  servo[2].write(a2);
  servo[3].write(a3);
  servo[4].write(a3);
  servo[5].write(a4);
  servo[6].write(a4);
  servo[7].write(a5);
  servo[8].write(a6);
  nh.spinOnce();
  delay(1);
}

double findAngle(int roll, int pitch)
{
  return ((atan2(roll,pitch))*180/pi);
}
