#include <Servo.h>
#include <Wire.h>

#define address 0x1E

int servoPin5 = 11;
int servoPin6 = 12;
int x,y,z;

//#define MAX_FDIR 1900
//#define MIN 1500
//#define MAX_RDIR 1100
Servo t5,t6;

#define LED_PIN 13
bool blinkState = false;

void setup()
{ 
  //Initialize Serial and I2C COMMUNICATIONS
  Serial.begin(9600);
  Wire.begin();
  digitalWrite(22,HIGH);
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
  delay(1000);
   
  t5.attach(servoPin5);
  t6.attach(servoPin6);
}

void loop() 
{
  static int signal_t5 = 1100;
  static int signal_t6 = 1100;
  
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
  
  if(x=45) // Forward
  {
    signal_t5=1150;
    signal_t6=1850;
  }
  
  else if(x>45)  // Backward
  {
    signal_t5=1850;
    signal_t6=1150;
  }
  
   
  else if(x=4)  // Left
  {
    signal_t5=1150;
    signal_t6=1350;
  }
  
  else if(x=47)  // Right
  {
    signal_t5=1350;
    signal_t6=1150;
  }
  
  t5.writeMicroseconds(signal_t5);
  t6.writeMicroseconds(signal_t6);
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
  Serial.print("Signal");
  Serial.println(signal_t5);
  Serial.print(",");
  Serial.println(signal_t6);  
  delay(100);

  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
