#include <SparkFun_MS5803_I2C.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

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

MS5803 sensor(ADDRESS_HIGH);
//Create variables to store results
float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;

// Create Variable to store altitude in (m) for calculations;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)

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
}

void loop()
{
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
  }
    
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
