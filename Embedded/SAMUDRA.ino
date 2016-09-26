#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>
#include <SparkFun_MS5803_I2C.h>
#include <ros.h>
#include <geometry_msgs/Pose2D.h>
#include <sensor_msgs/Imu.h>

// Thrusters parameters
#define MAX_FDIR 1900
#define MIN 1500
#define MAX_RDIR 1100

int servoPin1 = 8;
int servoPin2 = 9;
int servoPin3 = 10;
int servoPin4 = 11;
int servoPin5 = 12;
int servoPin6 = 13;


// AHRS parameters
double ox,oy,oz; //orientation ke x,y,z. These are made global so that they will be automatically be updated via ROS callback functions
double lax,lay,laz; //Linear Acceleration in x, and z similarly.
double avx,avy,avz; //Angular velocity x,y,z
double x,y,theta; //Heading Parameters
double xt,yt,thetat; //TrueHeading Parameters

ros::NodeHandle n;
ros::Subscriber<sensor_msgs::Imu> s1("imu/data", updateData );
ros::Subscriber<geometry_msgs::Pose2D> s2("imu/HeadingTrue", updateHeading );
ros::Subscriber<geometry_msgs::Pose2D> s3("imu/HeadingTrue_degree", updateHeadingTrueDegree );

// LCD parameters
LiquidCrystal lcd(31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51);
String lcd_print = "samudra niot 2016";

MS5803 sensor(ADDRESS_HIGH);


void setup()
{
  // AHRS Initialization
  n.initNode();
  Serial.begin(115200); //Same baud rate as that of the sensor
  n.subscribe(s1);
  n.subscribe(s2);
  n.subscribe(s3);
}

