#include <ros.h>
#include <geometry_msgs/Pose2D.h>
#include <sensor_msgs/Imu.h>



void updateData(const sensor_msygs::Imu& msg)
{
  updateHeadingTrueDegree(const geometry_msgs::Pose2D& msg);
  
  //Orientation,LA and AV would be updated :)
  ox = msg.orientation.x;
  oy = msg.orientation.y;
  oz = msg.orientation.z;

  lax = msg.linear_acceleration.x;
  lay = msg.linear_acceleration.y;
  laz = msg.linear_acceleration.z;

  avx = msg.angular_velocity.x;
  avy = msg.angular_velocity.y;
  avz = msg.angular_velocity.z;

  Roll = msg.r;
  Pitch = msg.p;
  Yaw = msg.y;

  led_status(HIGH, LOW, LOW);

  accX = (compAcc * accX + (1 - compAcc) * (lax)) / 100.00;
  accY = (compAcc * accY + (1 - compAcc) * (lay)) / 100.00;
  accZ = (compAcc * accZ + (1 - compAcc) * (laz)) / 100.00;

  
  kalmanX.setAngle(Roll);
  gyroXangle = Roll;

  kalmanY.setAngle(Pitch);
  gyroYangle = Pitch;

  kalmanZ.setAngle(Yaw);
  gyroZangle = Yaw;
  
}
/*
  roll = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  pitch = atan2(-accX, accZ) * RAD_TO_DEG;
*/
void updateDatamain(const sensor_msygs::Imu& msg,)
  {
  updateHeadingTrueDegree(const geometry_msgs::Pose2D& msg);
  
  ox = msg.orientation.x;
  oy = msg.orientation.y;
  oz = msg.orientation.z;

  lax = msg.linear_acceleration.x;
  lay = msg.linear_acceleration.y;
  laz = msg.linear_acceleration.z;

  avx = msg.angular_velocity.x;
  avy = msg.angular_velocity.y;
  avz = msg.angular_velocity.z;

  Roll = msg.r;
  Pitch = msg.p;
  Yaw = msg.y;

  led_status(HIGH, LOW, LOW);

  accX = (compAcc * accX + (1 - compAcc) * (lax)) / 100.00;
  accY = (compAcc * accY + (1 - compAcc) * (lay)) / 100.00;
  accZ = (compAcc * accZ + (1 - compAcc) * (laz)) / 100.00;

 
  gyroRate(avx, avy, avz);

  if ((Pitch < -90 && kalPitch > 90) || (Pitch > 90 && kalPitch < -90)) {             //restriction of pitch ;
    kalmanY.setAngle(Pitch);
    kalPitch = Pitch;
    gyroYangle = Pitch;
  }
  else
    kalPitch = kalmanY.getAngle(Pitch, gyroPitch, dt);

  if (abs(kalPitch) > 90)
  {
    //avx = -avx;
    kalRoll = kalmanX.getAngle(Roll, -gyroRoll, dt); // Calculate the angle using a Kalman filter
    gyroXangle -= gyroRoll * dt;
  }
  else
  {
    kalRoll = kalmanX.getAngle(Roll, gyroRoll, dt);
    gyroXangle += gyroRoll * dt;
  }

  double rollAngle = kalRoll * DEG_TO_RAD;
  double pitchAngle = kalPitch * DEG_TO_RAD;

if ((Yaw < -90 && kalYaw > 90) || (Yaw > 90 && kalYaw < -90)) {
    kalmanZ.setAngle(Yaw);
    kalYaw = Yaw;
    gyroZangle = Yaw;
  }
  else
    kalYaw = kalmanZ.getAngle(Yaw, gyroYaw, dt);
  // Calculate gyro angle without any filter
  gyroYangle += gyroPitch * dt;
// gyro value for removing drift
  gyroZangle += gyroYaw * dt;

  // Reset the gyro angles when they has drifted too much
  if (gyroXangle < -180 || gyroXangle > 180)
    gyroXangle = kalRoll;
  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalPitch;
  if (gyroZangle < -180 || gyroZangle > 180)
    gyroZangle = kalYaw;
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
}

void updateHeading(const geometry_msgs::Pose2D& msg)
{
  x = msg.x;
  y = msg.y;
  theta = msg.theta;

  double dt = (double)(micros() - timer) / 1000000;

  timer = micros();
  double rollAngle = kalRoll * DEG_TO_RAD;
  double pitchAngle = kalPitch * DEG_TO_RAD;
}

void updateHeadingTrueDegree(const geometry_msgs::Pose2D& msg)
{
  xt = msg.x;
  yt = msg.y;
  thetat = msg.theta;
}
void gyroRate(double avx, double avy, double avz)
{
  //again it is averaging function used to remove noise
  //it is executed in each iteration of loop()
  gyroRoll = (compGyroFilter * gyroRoll + (1 - compGyroFilter) * avx);
  gyroPitch = (compGyroFilter * gyroPitch + (1 - compGyroFilter) * avy);
  gyroYaw = (compGyroFilter * gyroYaw + (1 - compGyroFilter) * avz);
}

ros::NodeHandle n;
ros::Subscriber<sensor_msgs::Imu> s1("imu/data", updateData );
ros::Subscriber<geometry_msgs::Pose2D> s2("imu/HeadingTrue", updateHeading );
ros::Subscriber<geometry_msgs::Pose2D> s3("imu/HeadingTrue_degree", updateHeadingTrueDegree );




