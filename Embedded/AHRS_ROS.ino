void updateData(const sensor_msgs::Imu& msg)
{
  Serial.print(msg.orientation.x);
  Serial.print(msg.orientation.y);
  Serial.print(msg.orientation.z);  
  Serial.println();
    
  lax = msg.linear_acceleration.x;
  lay = msg.linear_acceleration.y;
  laz = msg.linear_acceleration.z;
    
  avx = msg.angular_velocity.x;
  avy = msg.angular_velocity.y;
  avz = msg.angular_velocity.z;
  
  Serial.print(ox);
  Serial.print(" ");
  Serial.print(oy);
  Serial.print(" ");
  Serial.print(oz);
  Serial.print(" ");
    
  Serial.println("lax");
  Serial.print(" \t");
  Serial.println(lax);
  Serial.print(" \t");
  Serial.print(lay);
  Serial.print(" ");
  Serial.print(laz);
  Serial.print(" ");
     
  Serial.println(avx);
  Serial.print(" ");
  Serial.print(avy);
  Serial.print(" ");
  Serial.print(avz);
  Serial.print(" ");    
}

void updateHeading(const geometry_msgs::Pose2D& msg)
{
  Serial.print("Updating Heading\n");
    x = msg.x;
    y = msg.y;
    theta = msg.theta;
    Serial.println(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.print(theta);
    Serial.print(" ");
}

void updateHeadingTrueDegree(const geometry_msgs::Pose2D& msg)
{
  xt = msg.x;  
  yt = msg.y;
  thetat = msg.theta;
}
