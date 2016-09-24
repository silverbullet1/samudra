
#include <Servo.h>
#include <Wire.h>
//#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter
#include <LiquidCrystal.h>


Servo sfl;
Servo sfr;
Servo scl;
Servo scr;
Servo sbl;
Servo sbr;


LiquidCrystal lcd(31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51);
String lcd_print = "samudra niot 2016";

double  ox, oy, oz; //orientation ke x,y,z. These are made global so that they will be automatically be updated via ROS callback functions
double lax, lay, laz; //Linear Acceleration in x, and z similarly.
double avx, avy, avz; //Angular velocity x,y,z
double x, y, theta; //Heading Parameters
double xt, yt, thetat; //TrueHeading Parameters
double compAngleSet = 0.95;
double compRateSet = 0.95;
double compGyroFilter = 0.90;
double compAcc = 0.90;


//Kalman kalmanX; // Create the Kalman instances
//Kalman kalmanY;
bool file = false;
uint32_t lcd_scheduler;
uint32_t ack_scheduler;
uint32_t timer_sp;
/* IMU Data */
double lax, lay, laz;
double accX, accY, accZ;
int16_t tempRaw;
double gyroRoll = 0.0;
double gyroPitch = 0.0;
double gyroYaw = 0.0;
double gyroX, gyroY, gyroZ;

double roll, pitch, yaw;

double accXangle, accYangle; // Angle calculate using the accelerometer
//double temp; // Temperature
double gyroXangle, gyroYangle, gyroZangle; // Angle calculate using the gyro
double compAngleX, compAngleY, compAngleZ; // Calculate the angle using a complementary filter
double kalAngleX, kalAngleY, kalAngleZ; // Calculate the angle using a Kalman filter
double kalRoll, kalPitch, kalYaw;

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data
float output = 0.0;
unsigned long int fl_pwm,fr_pwm,bl_pwm,br_pwm,cl_pwm,cr_pwm;

void led_status(bool r, bool y, bool b) {
  digitalWrite(red_led, y);
  digitalWrite(yellow_led, r);
  digitalWrite(blue_led, b);

}
void led_display(bool f)
{
  if (f == true)
  {
    led_status(LOW, LOW, HIGH);
  }
  else
  {
    led_status(LOW, HIGH, HIGH);
  }
}

//PID CLASS
class PID_SAM
{

  public:

    PID_SAM(double, double, double, double = -500, double = 500);

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

PID_SAM PIDrol_rate(p_rol_rate , i_rol_rate , d_rol_rate);
double out_rate_x;


//PITCH RATE PID
double p_pitch_rate = 0;
double i_pitch_rate = 0;
double d_pitch_rate = 0;

PID_SAM PIDpitch_rate(p_pitch_rate , i_pitch_rate , d_pitch_rate);
double out_rate_y;


//YAW RATE PID
double p_yaw_rate = 0;
double i_yaw_rate = 0;
double d_yaw_rate = 0;

PID_SAM PIDyaw_rate(p_yaw_rate , i_yaw_rate , d_yaw_rate);
double out_rate_z;


//ROLL ANGLE STABILIZE PID
double p_rol_angle = 0;
double i_rol_angle = 0;
double d_rol_angle = 0;

PID_SAM PIDrol_angle(p_rol_angle , i_rol_angle , d_rol_angle);
double out_angle_x;


//PITCH ANGLE STABILIZE PID
double p_pitch_angle = 0;
double i_pitch_angle = 0;
double d_pitch_angle = 0;
PID_SAM PIDpitch_angle(p_pitch_angle , i_pitch_angle , d_pitch_angle);
double out_angle_y;

//YAW ANGLE STABILIZE PID
double p_yaw_angle = 0;
double i_yaw_angle = 0;
double d_yaw_angle = 0;
PID_SAM PIDyaw_angle(p_yaw_angle , i_yaw_angle , d_yaw_angle);
double out_angle_z;

//ALTITUDE STABILIZATION PID
double p_alt = 0;
double i_alt = 0;
double d_alt = 0;
PID_SAM PIDalt(p_alt , i_alt , d_alt);
double out_alt;

//PID AND CASCADING SECTION
//rate pid is always on. However, angle pid block can be switched on or off usinf variable pid_angle
//pid_rate_angle is used for cascading angle pid output to rate pid input IF it is true
boolean pid_rate_angle = false;
boolean pid_angle = true;
boolean pid_alt = true;


void setup() {
  // Make sure all motor controller pins start low
  delay(100);
  n.initNode();
  n.subscribe(s1);
  n.subscribe(s2);
  n.subscribe(s3);

  Serial.begin(115200);
  //LCD INITIALIZATION
  pinMode(LCD_BACKLIGHT, OUTPUT);
  digitalWrite(LCD_BACKLIGHT, HIGH);
  lcd.begin(16, 2);
  //led_status(red, yellow, blue);

#if lcd_enable
  lcd.setCursor(3, 0);
  lcd.print(VERSION);
  lcd.setCursor(3, 1);
  lcd.print("AIACTR-AUV");
#endif

  sfl.attach(fl);
  sfr.attach(fr);
  scl.attach(cl);
  scr.attach(cr);
  sbl.attach(bl);
  sbr.attach(br);
  Wire.begin();
  //LED pins are geting initialize
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  lcd_status(file);

  updateData(const sensor_msgs::Imu & msg); //for linear acceleration and angular velocity
  updateHeading(const geometry_msgs::Pose2D & msg); //heading

  updateHeadingTrueDegree(const geometry_msgs::Pose2D & msg); //true degree
  /*
     // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
     // We then convert it to 0 to 2π and then from radians to degrees
     accYangle = (atan2(accX, accZ) + PI) * RAD_TO_DEG;0
     accXangle = (atan2(accY, accZ) + PI) * RAD_TO_DEG;

     kalmanX.setAngle(accXangle); // Set starting angle
     kalmanY.setAngle(accYangle);
     gyroXangle = accXangle;
     gyroYangle = accYangle;
     compAngleX = accXangle;
     compAngleY = accYangle;
  */
  sfl.writeMicroseconds(MIN);
  sfr.writeMicroseconds(MIN);
  scl.writeMicroseconds(MIN);
  scr.writeMicroseconds(MIN);
  sbl.writeMicroseconds(MIN);
  sbr.writeMicroseconds(MIN);
  delay(1000);
  led_status(HIGH, HIGH, HIGH);

  timer_sp = millis();
  lcd_scheduler = millis();
  ack_scheduler = millis();
  file_scheduler = millis();
}

void loop() {
  if (millis() - lcd_scheduler > 2000) {
    lcd_status(ahrs, file);
    lcd_scheduler = millis();
  }
  controller();
  static int s2 = 1500;
  static int signal1 = 1500;
  static uint32_t timer = millis();
  static bool reverseDir = true;

  updateData(const sensor_msgs::Imu & msg); //for linear acceleration and angular velocity
  updateHeading(const geometry_msgs::Pose2D & msg); //heading
  updateHeadingTrueDegree(const geometry_msgs::Pose2D & msg);

  if ((Roll > 110 && Roll < 125) || Pitch > 68 )
  {
    if (millis() - timer >= 1000)
    {
      timer = millis();
      //Serial.println(signal);

      if (signal1 > MAX_FDIR && s2 < MAX_RDIR)
      {
        reverseDir = false;
      }
      else if (signal1 < MAX_FDIR && s2 > MAX_RDIR)
      {
        reverseDir = true;
      }

      if (reverseDir == true)
      {
        signal1 += 100 ;
        s2 -= 100;
      }
      else
      {
        signal1 -= 100;
        s2 += 100;
      }
    }
  }
  Serial.print("fl\t");
  sfl.writeMicroseconds(signal1);
  Serial.print("fr\t");
  sfr.writeMicroseconds(s2);
  Serial.print("cl\t");
  scl.writeMicroseconds(signal1);
  Serial.print("cr\t");
  scr.writeMicroseconds(s2);
  Serial.print("bl\t");
  sbl.writeMicroseconds(signal1);
  Serial.print("bf\t");
  sbr.writeMicroseconds(s2);

  led_display(file);
  Serial.print(ox);
  Serial.print(" ");
  Serial.print(oy);
  Serial.print(" ");
  Serial.print(oz);
  Serial.print(" ");

  Serial.print(lax);
  Serial.print(" ");
  Serial.print(lay);
  Serial.print(" ");
  Serial.print(laz);
  Serial.print(" ");


  Serial.print(avx);
  Serial.print(" ");
  Serial.print(avy);
  Serial.print(" ");
  Serial.print(avz);
  Serial.print(" ");


  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(theta);
  Serial.print(" ");

  Serial.print("\n");
  n.spinOnce();
  delay(400);
}
