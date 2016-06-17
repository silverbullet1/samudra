//#include "sensors_actuators.h"

//***************************************************
//***************************************************
//####     ####
//#  #     #  #      ######  ######## ########
//#  ####  #  ####   #    ## #  ##  # #  ##  #
//      ##       ##  ####  # #  ##  # #  ##  #
//#  ##  # #  ##  # ##     # #  ##  # #  ##  #
//#  ##  # #  ##  # #  ##  # #  ##  # ##    ##
//#     ## #     ## ##     # ##     #  ##  ##
// # ####   # ####   #######  #######   ####
//
//Sensors and Actuators for BBAUV 2.0
//Firmware Version :             v1.2
//
// Written by Goh Eng Wei
// Change Log for v1.2:
//
//***************************************************
//***************************************************
//***************************************************

//C++ Header for Eclipse plugin compatibility
#include "sensors_actuators.h"

//Constant declaration
#include <Arduino.h>
#include <ros.h>
#include <smcDriver_v2.h> //Simple Motor Controller from Pololu Robotics and Electronics
#include <Adafruit_ADS1015.h> //Display
#include <Wire.h> //For I2C
#include <Adafruit_CharacterOLED.h>
#include <Thrusters.h>
#include <Servo.h>
#include <HIH613x.h>
#include <LEDS.h>

//Messages to communicate with ROS
#include <bbauv_msgs/thruster.h>   //thruster speed
#include <bbauv_msgs/manipulator.h> //For servos control
#include <bbauv_msgs/hull_status.h> //Temperature, Water Sensor
#include <bbauv_msgs/openups.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int8.h>

#include "defines.h"

//Constants definition
#define PRESSURE_TYPE PRESSURE_TYPE_GAUGE_30
#define DEBUG_MODE DEBUG_BB
#define LCD_MODE LCD_OFF
#define VERSION 1.2

//Timming variables - to ensure the loop run at correct frequency
static uint32_t currentTime,loopTime, fast_loop,time_elapsed, medium_loop, slow_loop;
uint32_t lcd_ctr = 0;
uint32_t slow_loop_ctr;

//Declare Subscribers, Publishers & Call back functions in ROS
ros::NodeHandle nh;

//LCD Subscriber
#if LCD_MODE == LCD_ON
void getLCDCommand(const std_msgs::Int8 &msg);
ros::Subscriber<std_msgs::Int8> lcd_sub("lcd_commands",&getLCDCommand);
#endif

//LED Strips subscriber
void getLEDStrips(const std_msgs::Int8 &msg);
ros::Subscriber<std_msgs::Int8> led_strips_sub("led_strips",&getLEDStrips);

//Battery reading - openups
void getBattery(const bbauv_msgs::openups &msg);
ros::Subscriber<bbauv_msgs::openups> batt_sub("battery_voltage",&getBattery);

//Thruster Controller
void getThrusterSpeed(const bbauv_msgs::thruster &msg);
ros::Subscriber<bbauv_msgs::thruster> thruster_sub("thruster_speed",&getThrusterSpeed);

//Manipulator Controller
void getManipulator(const bbauv_msgs::manipulator &msg);
ros::Subscriber<bbauv_msgs::manipulator> manipulator_sub("manipulators",&getManipulator);

//Hull Status Publishers - Temperature, Water Sensor, Humidity Sensor

bbauv_msgs::hull_status env_msg;
ros::Publisher env_pub("hull_status", &env_msg);
HIH613x humid;

//Pressure publisher

std_msgs::Int16 pressure_msg;
ros::Publisher pressure_pub("pressure_data",&pressure_msg);

//Motor Driver definitions
bbauv_msgs::thruster thrusterSpeed;

smcDriver mDriver(&Serial1); //Use Serial1 to handle UART communication with motor controllers
Thrusters videoray(RAY_1,RAY_2);

//Leak sensor counter
uint8_t leak_ctr = 0;

//humidity sensor counter
uint8_t hum_temp_count = 0;

//Torpedo Delay
uint16_t torp_ctr = 0,torp_ctr2 = 0;
//OLED LCD Driver
#if LCD_MODE == LCD_ON
Adafruit_CharacterOLED lcd(A3, A4, A5, A6, A7, A8, A9);
#endif

LEDS led(10,9,8);
//ADC definitions
Adafruit_ADS1115 ads1115;

//Pressure Sensor Definitions

int16_t pressure;

void setup()
{
	//Debug Mode: to be removed by the compiler if not in debug mode.
	#if DEBUG_MODE == DEBUG_BB
	  Serial2.begin(9600);
	  Serial2.println("Debug Mode");
	#endif
	Wire.begin();
	//Initialize ROS: publishers, subscribers
    nh.initNode();
    lcd_init();
    topics_init();
    manipulators_init();
    leds_init();
    pressure_init();
    motors_init();
    humid_init();
    lcd_display();
    //Initialize MainLoop Timing variables
	time_elapsed=0;
	currentTime=millis();
	loopTime=currentTime;
}

void humid_init()
{
	humid.init();
	humid.startRead();
	delay(60);
	if(humid.singleRead() == 1)
	{
		lcd.clear();
		lcd.setCursor(0,0);
		//lcd.print("HUMID OK");
	} else lcd.print("HUMID NOK");
	delay(1000);
}
void pressure_init()
{
	lcd.clear();
	lcd.setCursor(0,0);
	if(readPressure() > 3000)
	{
		lcd.print("PRES OK");
	} else lcd.print("PRES NOK");
	delay(1000);
}

void leds_init()
{
	for(int i=0;i<10;i++)
	{
		led.colour(i);
		delay(200);
	}
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("LEDS OK");
	delay(1000);
}
void lcd_init()
{
	pinMode(A3, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
	pinMode(A6, OUTPUT);
	pinMode(A7, OUTPUT);
	pinMode(A8, OUTPUT);
	pinMode(A9, OUTPUT);
    // set up the LCD's number of rows and columns:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.setCursor(0,0);
    lcd.print("BBAUV 2.0");
    lcd.setCursor(0,1);
    lcd.print("SYSTEMS v");
    lcd.setCursor(10,1);
    lcd.print(VERSION);
    delay(2000);
}
void motors_init()
{
	//Initialize Motor Drivers and serial port:
	Serial1.begin(115200);
	mDriver.init();
	videoray.mov(0,0);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("MOTORS OK");
	delay(1000);
}

void topics_init()
{
	nh.subscribe(thruster_sub);
	nh.subscribe(manipulator_sub);
	nh.subscribe(batt_sub);
	nh.subscribe(led_strips_sub);
	#if LCD_MODE == LCD_ON
	    nh.subscribe(lcd_sub);
	#endif
	nh.advertise(env_pub);
	nh.advertise(pressure_pub);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("TOPICS OK");
	delay(1000);
}

void manipulators_init()
{
	//Initialize Manipulators
	pinMode(MANI_1,OUTPUT);
	pinMode(MANI_2,OUTPUT);
	pinMode(MANI_3,OUTPUT);
	pinMode(MANI_4,OUTPUT);
	pinMode(MANI_5,OUTPUT);
	pinMode(MANI_6,OUTPUT);
	pinMode(MANI_7,OUTPUT);
}

void lcd_display()
{
    lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("SYSTEM OK");
	delay(1000);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("W:");
	lcd.setCursor(5,0);
	lcd.print("T:");
	lcd.setCursor(10,0);
	lcd.print("H:");
	lcd.setCursor(0,1);
	lcd.print("B1:");
	lcd.setCursor(8,1);
	lcd.print("B2:");
}
void loop()
{
  currentTime=millis();
  //100 Hertz Loop for Pressure Sensor filtering
  if( currentTime >= (fast_loop + 10))
  {
#if DEBUG_MODE == DEBUG_BB
	int32_t val = millis();
    #endif
    readPressureFilter();
    #if DEBUG_MODE == DEBUG_BB
     Serial2.print(currentTime - fast_loop);
     Serial2.print(" ");
     //Serial2.println(millis()-val);
    #endif
    fast_loop = currentTime;
  }

  //20 Hertz Loop for Control Loop
  currentTime=millis();

  if( currentTime >= (medium_loop + 50))
  {
     #if DEBUG_MODE == DEBUG_BB
      Serial2.print(currentTime - medium_loop);
      Serial2.print(" ");
    #endif
    runThruster();
    pressure_msg.data = pressure;
    pressure_pub.publish(&pressure_msg);
    nh.spinOnce();
    medium_loop = currentTime;
    /*
    if(torp_ctr == 1)
	{
		digitalWrite(MANI_3,LOW);
		torp_ctr--;
	} else if(torp_ctr >1)
    {
		torp_ctr--;
    }
    if(torp_ctr2 == 1)
	{
		digitalWrite(MANI_4,LOW);
		torp_ctr2--;
	} else if(torp_ctr2 >1)
	{
		torp_ctr2--;
	}
	*/
  }

 //1Hertz Loop for non-critical sensors
 currentTime=millis();

 if(currentTime >=(slow_loop + 333))
 {
   switch(slow_loop_ctr)
   {
     case 0:
       humid.startRead();
       break;
     case 1:
       humid.singleRead();
       env_msg.Temp0 = humid.getTemp();
       env_msg.Humidity = humid.getHumidity();
       lcd.setCursor(7,0);
       lcd.print(round(env_msg.Temp0));
       lcd.setCursor(12,0);
       lcd.print(round(env_msg.Humidity));
       break;
     case 2:
       readWater();
       env_pub.publish(&env_msg);
       break;
   }
   if(slow_loop_ctr != 3)  slow_loop_ctr++;
   else  slow_loop_ctr = 0;
    #if DEBUG_MODE == DEBUG_BB
    Serial2.println(currentTime - slow_loop);
    #endif
   slow_loop = currentTime;
 }
}

//Supporting functions:
int32_t fmap(int32_t input, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max){
  return (input- in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Sensor Tasks Callbacks ---------------------------------------------------------
int16_t readPressure()
{
    //int32_t pressure;
    //float temp_depth;
    int16_t adc;
 #if PRESSURE_TYPE == PRESSURE_TYPE_GAUGE_30
    adc = ads1115.readADC_SingleEnded(0);
 #elif PRESSURE_TYPE == PRESSURE_TYPE_ABSOLUTE_100
    adc = ads1115.readADC_SingleEnded(1);
 #endif

 #if DEBUG_MODE == DEBUG_BB
    //Serial2.println(temp_depth);
 #endif

 return adc;
}

/* Discrete Low Pass Filter to reduce noise in signal */
void readPressureFilter()
{
   int16_t temp = readPressure();
   if(temp != 0)
   {
	   pressure = pressure + LPF_CONSTANT*(float)(temp - pressure);
   }
}

void getLEDStrips(const std_msgs::Int8 &msg)
{
	led.colour(msg.data);
}
void readWater()
{
    env_msg.WaterDetA = 1-digitalRead(WaterPin1);
    env_msg.WaterDetB = 1-digitalRead(WaterPin2);
    env_msg.WaterDetC = 1-digitalRead(WaterPin3);
    //turn-on LED when water is detected
#if LCD_MODE == LCD_ON
    lcd.setCursor(2, 0);
    if(env_msg.WaterDetC)
    {
    	if(leak_ctr >5)
    	{
    		emergency_mode(7);
    	} else
    	{
    		leak_ctr++;
    	}
    } else leak_ctr = 0;

    if(env_msg.WaterDetA||env_msg.WaterDetB)
    {
    	lcd.print("T");
    	emergency_mode(4);
    }
    else lcd.print("F");
#endif
}

void emergency_mode(int color)
{
	int surface = 800;
	videoray.mov(0,0);

	while(1)
	{
		mDriver.setMotorSpeed(THRUSTER_3,surface);
		mDriver.setMotorSpeed(THRUSTER_4,surface);
		mDriver.setMotorSpeed(THRUSTER_5,surface);
		mDriver.setMotorSpeed(THRUSTER_6,surface);
		mDriver.setMotorSpeed(THRUSTER_7,0);
		mDriver.setMotorSpeed(THRUSTER_8,0);
		led.colour(color);
		delay(100);
		led.colour(9);
		delay(100);
	}

}
void runThruster()
{
    videoray.mov(thrusterSpeed.speed1,thrusterSpeed.speed2);
    mDriver.setMotorSpeed(THRUSTER_3,thrusterSpeed.speed3);
    mDriver.setMotorSpeed(THRUSTER_4,thrusterSpeed.speed4);
    mDriver.setMotorSpeed(THRUSTER_5,thrusterSpeed.speed5);
    mDriver.setMotorSpeed(THRUSTER_6,thrusterSpeed.speed6);
    mDriver.setMotorSpeed(THRUSTER_7,thrusterSpeed.speed7);
    mDriver.setMotorSpeed(THRUSTER_8,thrusterSpeed.speed8);
}

//-----------------------ROS Callbacks---------------------------------------//
#if LCD_MODE == LCD_ON
void getLCDCommand(const std_msgs::Int8 &msg)
{
	switch(msg.data)
	{
	case 1:
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("System booted.");
		delay(5000);
		break;
	case 2:
		lcd.setCursor(0,1);
		lcd.print("TC Fuck off!");
		break;
	case 3:
		lcd.setCursor(0,1);
		lcd.print("We love Hallin!:)");
		break;
	default:
		break;
	}
}
#endif

void getBattery(const bbauv_msgs::openups &msg)
{
	lcd.setCursor(3,1);
	lcd.print((float)msg.battery1/10);
	lcd.setCursor(11,1);
	lcd.print((float)msg.battery2/10);
}
void getManipulator(const bbauv_msgs::manipulator &msg)
{
	int data = msg.mani_data;
	//Manipulator 1
	data &= 0b00000001;
	(data == 0x01) ? digitalWrite(MANI_1,HIGH) :digitalWrite(MANI_1,LOW);

	/*Legacy code
	 * (msg.servo3) ?	digitalWrite(MANI_3,HIGH) :digitalWrite(MANI_3,LOW);
	//Fire Left Torpedo
	if (msg.servo3)
	{
		//Fires Torpedo first
		digitalWrite(MANI_3,HIGH);
		torp_ctr = 4;
	} else
	{
		//Keep Torpedo steady
		digitalWrite(MANI_3,LOW);
	}
	//Fire Right Torpedo
	if (msg.servo4)
	{
		//Fire Torpedo
		digitalWrite(MANI_4,HIGH);
		torp_ctr2 = 4;
	} else
	{
		//Keep Torpedo steady
		digitalWrite(MANI_4,LOW);
	}
	(msg.servo5) ?	digitalWrite(SERVO_5,HIGH) :digitalWrite(SERVO_5,LOW);
	//(msg.servo6) ?	digitalWrite(SERVO_6,HIGH) :digitalWrite(SERVO_6,HIGH);
	//(msg.servo7) ?	digitalWrite(SERVO_7,HIGH) :digitalWrite(SERVO_7,HIGH);
	 * */
}
void getThrusterSpeed(const bbauv_msgs::thruster &msg)
{
    thrusterSpeed=msg;
}
