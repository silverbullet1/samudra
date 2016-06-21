#include <SparkFun_MS5803_I2C.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Servo.h>

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

#define address 0x1E

int16_t ax, ay, az;
int16_t gx, gy, gz;
int x,y,z; //triple axis data
double Roll;
double Pitch;
double Yaw;

//Create variables to store results
float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;

// Create Variable to store altitude in (m) for calculations;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)

int servoPin1 = 10;
int servoPin2 = 10;
int servoPin3 = 10;
int servoPin4 = 10;
int servoPin5 = 10;
int servoPin6 = 10;

static bool reverseDir1 = true;
static bool reverseDir2 = true;
static bool reverseDir3 = true;
static bool reverseDir4 = true;
static bool reverseDir5 = true;
static bool reverseDir6 = true;

#define MAX_FDIR 1900
#define MIN 1500
#define MAX_RDIR 1100
Servo servo1,servo2,servo3,servo4,servo5,servo6;

#define LED_PIN 13
bool blinkState = false;

void setup()
{ 
  // Initializing of IMU 
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
   delay(500);
  pinMode(LED_PIN, OUTPUT);
  
  // Initializing of Magnetometer
  digitalWrite(22,HIGH);
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
  
  // Initializing Pressure Sensor
  sensor.reset();
  sensor.begin();
  pressure_baseline = sensor.getPressure(ADC_4096);
  
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);
  servo6.attach(servoPin6);
  //servo.writeMicroseconds(1500);// send" stop" signal
  //delay(1000);
}

void loop() 
{ 
  // Controlled by hmc and imu
  static int signal1 = 1000;  
  static int signal2 = 1000;
  // Controlled by pressure sensor 
  static int signal3 = 1000;
  static int signal4 = 1000;
  static int signal5 = 1000;
  static int signal6 = 1000;
  
  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Roll = atan2(ax, az) * 180/PI;
  Pitch = atan2(ax, sqrt(ay*ay + az*az)) * 180/PI;
  Yaw = atan2(ay,ax)* 180/PI;
  
  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
  //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available())
  {
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
  
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
    
  // Reading values from Pressure Sensor
  // To measure to higher degrees of precision use the following sensor settings:
  // ADC_256 
  // ADC_512 
  // ADC_1024
  // ADC_2048
  // ADC_4096
    
  // Read temperature from the sensor in deg C. This operation takes about 
  temperature_c = sensor.getTemperature(CELSIUS, ADC_512);
  
  // Read temperature from the sensor in deg F. Converting
  // to Fahrenheit is not internal to the sensor.
  // Additional math is done to convert a Celsius reading.
  temperature_f = sensor.getTemperature(FAHRENHEIT, ADC_512);
  
  // Read pressure from the sensor in mbar.
  pressure_abs = sensor.getPressure(ADC_4096);
  
  // Let's do something interesting with our data.
  
  // Convert abs pressure with the help of altitude into relative pressure
  // This is used in Weather stations.
  pressure_relative = sealevel(pressure_abs, base_altitude);
  
  // Taking our baseline pressure at the beginning we can find an approximate
  // change in altitude based on the differences in pressure.   
  altitude_delta = altitude(pressure_abs , pressure_baseline);
  
  if(Roll>70) //necessary conditions ie, calibration
  {
    static uint32_t timer = millis();
    
    if(millis() - timer >= 1000) 
    {
      timer = millis();
      //Serial.println(signal);
      
      if(signal > MAX_FDIR) 
         reverseDir = false;
      
      else if (signal < MAX_RDIR) 
         reverseDir = true;
  
      if(reverseDir == true) 
          signal+=100 ;
    
      else 
          signal -=100; 
    
   }
   
  }
  else
  {
    servo.writeMicroseconds(1500);
  }
  servo.writeMicroseconds(signal);
  }
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
  Serial.print("signal");Serial.print("\t");
  Serial.print(signal);Serial.print("\t"); 
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
  // Report values via UART
  Serial.print("Temperature C = ");
  Serial.println(temperature_c);
  
  Serial.print("Temperature F = ");
  Serial.println(temperature_f);
  
  Serial.print("Pressure abs (mbar)= ");
  Serial.println(pressure_abs);
   
  Serial.print("Pressure relative (mbar)= ");
  Serial.println(pressure_relative); 
  
  Serial.print("Altitude change (m) = ");
  Serial.println(altitude_delta); 
  
  delay(100);
  

  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

double sealevel(double P, double A)
// Given a pressure P (mbar) taken at a specific altitude (meters),
// return the equivalent pressure (mbar) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
	return(P/pow(1-(A/44330.0),5.255));
}


double altitude(double P, double P0)
// Given a pressure measurement P (mbar) and the pressure at a baseline P0 (mbar),
// return altitude (meters) above baseline.
{
	return(44330.0*(1-pow(P/P0,1/5.255)));
}
