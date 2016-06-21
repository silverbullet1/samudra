#include <I2Cdev.h>
#include <LiquidCrystal.h>//LCD Library
#include <Wire.h>//I2C library used to read values from sensors like hmc5883l and mpu6050
#include "Kalman.h"//kalman filtering to fuse data from gyroscope and acceleromter and to output noise free angles


#define temp 0// 1 for priting temp values
#define angle 1 // 1 for printing angles
#define gyro 1// 1 for prinitng gyrocope values
#define acc 0// 1 for printing acceleration
#define magnet 0// 1 for prinitng magnetic field in x, y and z direction
#define mag_cal 0// 1 for printinfg calibrated magnetic constants

String data;
double yawError=0.00;
double altError=0.00;
//int servoPin = 10;
//int servoPin1 = 9;
#define MAX_FDIR 1900
#define MIN 1500
#define MAX_RDIR 1100
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;




//STATUS VARIABLES AND SBC COMMUNICATION
//bool mpu = false; //gets true when it detects mpu6050 connected
//bool hmc = false; //gets true when it detects hmc5883l connected

Kalman kalmanX, kalmanY, kalmanZ;
const uint8_t MPU6050 = 0x68; // If AD0 is logic low on the PCB the address is 0x68, otherwise set this to 0x69
const uint8_t HMC5883L = 0x1E;

double accX1, accY1, accZ1;
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double gyroRoll = 0.0;
double gyroPitch = 0.0;
double gyroYaw = 0.0;
double magX, magY, magZ;
int16_t tempRaw;

double roll, pitch, yaw;

double gyroXangle, gyroYangle, gyroZangle;
double kalRoll, kalPitch, kalYaw;

uint32_t timer;
uint8_t i2cData[14];

#define MAG0MAX 603
#define MAG0MIN -578 //
#define MAG1MAX 542
#define MAG1MIN -701 //
#define MAG2MAX 547
#define MAG2MIN -556

float magOffset[3] = {
  (MAG0MAX + MAG0MIN) / 2, (MAG1MAX + MAG1MIN) / 2, (MAG2MAX + MAG2MIN) / 2
};
double magGain[3];
//SETPOINT or ZERO REFERENCE
double zero_angle_roll;
double zero_angle_pitch;
double zero_angle_yaw;
double zero_rate_roll;
double zero_rate_pitch;
double zero_rate_yaw;
boolean zero_ref = false; //becomes true when zero_ref of gyro, kalman angles are calculated

//COMPLEMENTARY FILTER VALUES
//u can set the values of this variables from 0.80 to 0.97.
//higher the value, greater would be noise reduction effieciency from senosrs output 
double compAngleSet = 0.95;
double compRateSet = 0.95;
double compGyroFilter = 0.90;
double compAcc = 0.90;
unsigned long int f_speed;
unsigned long int b_speed;
unsigned long int threshold=150;
class PID_ATLAB
{

  public:

    PID_ATLAB(double, double, double, double = -500, double = 500);

    double Compute(double input, double zero, double Setpoint = 0.00);

    double ComputeFixedHz(double input, double zero, double sampletime, double Setpoint = 0.00);

    void SetOutputLimits(double, double);

    void SetTunings(double, double, double);
    void reset();

  private:

    double kp;
    double ki;
    double kd;
    int controllerDirection;

    unsigned long lastTime;
    double ITerm, lastInput;

    unsigned long SampleTime;
    double outMin, outMax;
    double output;

    double error;
    double SampleTimeInSec;
    double dInput;

};


//ROLL RATE PID
double p_rol_rate = 0;
double i_rol_rate = 0;
double d_rol_rate = 0;

PID_ATLAB PIDrol_rate(p_rol_rate , i_rol_rate , d_rol_rate);
double out_rate_x;


//PITCH RATE PID
double p_pitch_rate = 0;
double i_pitch_rate = 0;
double d_pitch_rate = 0;

PID_ATLAB PIDpitch_rate(p_pitch_rate , i_pitch_rate , d_pitch_rate);
double out_rate_y;


//YAW RATE PID
double p_yaw_rate = 0;
double i_yaw_rate = 0;
double d_yaw_rate = 0;

PID_ATLAB PIDyaw_rate(p_yaw_rate , i_yaw_rate , d_yaw_rate);
double out_rate_z;


//ROLL ANGLE STABILIZE PID
double p_rol_angle = 0;
double i_rol_angle = 0;
double d_rol_angle = 0;

PID_ATLAB PIDrol_angle(p_rol_angle , i_rol_angle , d_rol_angle);
double out_angle_x;


//PITCH ANGLE STABILIZE PID
double p_pitch_angle = 0;
double i_pitch_angle = 0;
double d_pitch_angle = 0;
PID_ATLAB PIDpitch_angle(p_pitch_angle , i_pitch_angle , d_pitch_angle);
double out_angle_y;

//YAW ANGLE STABILIZE PID
double p_yaw_angle = 0;
double i_yaw_angle = 0;
double d_yaw_angle = 0;
PID_ATLAB PIDyaw_angle(p_yaw_angle , i_yaw_angle , d_yaw_angle);
double out_angle_z;

//ALTITUDE STABILIZATION PID
double p_alt = 0;
double i_alt = 0;
double d_alt = 0;
PID_ATLAB PIDalt(p_alt , i_alt , d_alt);
double out_alt;

//PID AND CASCADING SECTION
//rate pid is always on. However, angle pid block can be switched on or off usinf variable pid_angle
//pid_rate_angle is used for cascading angle pid output to rate pid input IF it is true
boolean pid_rate_angle = false;
boolean pid_angle = true;
boolean pid_alt=true;

void setup() {
      servo0.attach(5);
      servo1.attach(6);
       servo2.attach(7);
      servo3.attach(8);
      servo4.attach(9);
      servo5.attach(10);

  delay(100);
  Serial.begin(115200);//buad rate for serial terminal and gui communication
  Wire.begin();
   //MPU6050 and HMC5883l is getting initialize here
  imuInitialize();
  delay(100);
  }

void loop() {
imu();
      zero_angle_roll = compAngleSet * zero_angle_roll + (1 - compAngleSet) * kalRoll;
      zero_angle_pitch = compAngleSet * zero_angle_pitch + (1 - compAngleSet) * kalPitch;
      zero_angle_yaw = compAngleSet * zero_angle_yaw + (1 - compAngleSet) * kalYaw;

      zero_rate_roll = compRateSet * zero_rate_roll + (1 - compRateSet) * gyroRoll;
      zero_rate_pitch = compRateSet * zero_rate_pitch + (1 - compRateSet) * gyroPitch;
      zero_rate_yaw = compRateSet * zero_rate_yaw + (1 - compRateSet) * gyroYaw;
      
      //it drives the motors and pid Compute function of angle pid and rate pud are being executred here
  controller();
}


