#include <I2Cdev.h>
#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

double Roll,Pitch,Yaw;

int servoPin1 = 10;
int servoPin2 = 9;
int servoPin3 = 8;
int servoPin4 = 7;

//#define MAX_FDIR 1900
//#define MIN 1500
//#define MAX_RDIR 1100
Servo t1,t2,t3,t4;

#define LED_PIN 13
bool blinkState = false;

void setup()
{ 
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  pinMode(LED_PIN, OUTPUT);
   
  t1.attach(servoPin1);
  t2.attach(servoPin2);
  t3.attach(servoPin3);
  t4.attach(servoPin4);
}

void loop() 
{
  static int signal_t1 = 1000;
  static int signal_t2 = 1000;
  static int signal_t3 = 1000;
  static int signal_t4 = 1000;
  
  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Roll = atan2(ax, az) * 180/PI;
  Pitch = atan2(ax, sqrt(ay*ay + az*az)) * 180/PI;
  Yaw=atan2(ay,ax)* 180/PI;
  
  // Now will start the if and else-if statements that will control the thrusters 
  // like we control we control the motors for turning the lfr
  // give the proper conditions for ax,ay,az,gx,gy,gz or for roll, pitch and yaw
  
  if(Roll=45) // Upaward
  {
    signal_t1=1150;
    signal_t2=1850;
    signal_t3=1150;
    signal_t4=1850;
  }
  
  else if(Roll>45)  // Downward
  {
    signal_t1=1850;
    signal_t2=1150;
    signal_t3=1850;
    signal_t4=1150;
  }
  
   
  else if(Roll=4)  // Roll
  {
    signal_t1=1150;
    signal_t2=1350;
    signal_t3=1150;
    signal_t4=1350;
  }
  
  else if(Roll=47)  // Pitch
  {
    signal_t1=1150;
    signal_t2=1150;
    signal_t3=1350;
    signal_t4=1350;
  }
  
  t1.writeMicroseconds(signal_t1);
  t2.writeMicroseconds(signal_t2);
  t3.writeMicroseconds(signal_t3);
  t4.writeMicroseconds(signal_t4);
  
  Serial.print("a/g:\t");
  Serial.print("Roll"); Serial.print("\t");
  Serial.print(Roll); Serial.print("\t");
  Serial.print("Pitch"); Serial.print("\t");
  Serial.print(Pitch); Serial.print("\t");
  Serial.print("Yaw"); Serial.print("\t");
  Serial.println(Yaw);Serial.print("\t");
  Serial.print("gx");Serial.print("\t");
  Serial.print(gx);Serial.print("\t");
  Serial.print("gy");Serial.print("\t");
  Serial.print(gy);Serial.print("\t");
  Serial.print("gz");Serial.print("\t");
  Serial.print(gz);Serial.print("\t");
  
  Serial.print("Signal");
  Serial.println(signal_t1);
  Serial.println(signal_t2);
  Serial.println(signal_t3);
  Serial.println(signal_t4);
  
  delay(100);

  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
