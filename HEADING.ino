#include <Servo.h>


// Arduino Wire library is required if I2Cdev I2CDE
#include "Wire.h"

// I2Cdev and HMC5883L must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "HMC5883L.h"

int servoPin1 = 10;
int servoPin2 = 11;
#define MAX_FDIR 1900
#define MIN 1500
#define MAX_RDIR 1100

Servo servo;
int signal1 = MIN;
int signal2 = MIN;
HMC5883L mag;

int16_t mx, my, mz;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    mag.initialize();
    servo.attach(servoPin1);
    servo.writeMicroseconds(signal1);
    servo.attach(servoPin2);
    servo.writeMicroseconds(signal2);
    
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
    
    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // read raw heading measurements from device
    mag.getHeading(&mx, &my, &mz);

    // display tab-separated gyro x/y/z values
    Serial.print("mag:\t");
    Serial.print(mx); Serial.print("\t");
    Serial.print(my); Serial.print("\t");
    Serial.print(mz); Serial.print("\t");
    
// To calculate heading in degrees. 0 degree indicates North
    float heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
      
      if(heading > 2*M_PI)
    heading -= 2*M_PI;

 float headingDegrees = heading * 180/M_PI;
    while (!Serial.available());
  if(headingDegrees>55)  //If we assume the initial angle to be 55 degrees and we intend to run the bot straight without any turns
 {
   signal1 -= 50;
   signal2 += 50;
 }else{
   signal2 -= 50;
   signal1 += 50;
 }
    servo.writeMicroseconds(signal1);
    servo.writeMicroseconds(signal2);

    Serial.print("heading:\t");
    Serial.print(heading * 180/M_PI);

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
