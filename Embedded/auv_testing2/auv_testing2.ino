#include <Servo.h>
#include <Wire.h>
//#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter
#include <LiquidCrystal.h>

#define MIN  1000
#define MID  1500
#define MAX  2000

#define PIN_1  9
#define PIN_2  8
#define PIN_3  10
#define PIN_4  11
#define PIN_5  12
#define PIN_6  7


Servo sfl;
Servo sfr;
Servo scl;
Servo scr;
Servo sbl;
Servo sbr;

void setup() {
  Serial.begin(115200);
  Serial.println("SAMUDRA");
  sfl.attach(PIN_1);
  sfr.attach(PIN_2);
  scl.attach(PIN_3);
  scr.attach(PIN_4);
  sbl.attach(PIN_5);
  sbr.attach(PIN_6);
  sfl.writeMicroseconds(MID);
  sfr.writeMicroseconds(MID);
  scl.writeMicroseconds(MID);
  scr.writeMicroseconds(MID);
  sbl.writeMicroseconds(MID);
  sbr.writeMicroseconds(MID);
}

int s1 = MID;
int s2 = MID;

void loop()
{

  if (Serial.available() < 2)
    return;
  char t = Serial.read();
  char c = Serial.read();
  if (c == '+')
    t == 'f' ? s1 += 100 : s2 += 100;
  if (c == '-')
    t == 'f' ? s1 -= 100 : s2 -= 100;
  Serial.print(t);Serial.print("\t");Serial.print(c);Serial.println("");

  s1 = constrain(s1, MIN, MAX);
  s2 = constrain(s2, MIN, MAX);

  Serial.print("fl\t");
  Serial.print(s1);
  sfl.writeMicroseconds(s1);
  Serial.print("\tfr\t");
  Serial.print(s2);
  sfr.writeMicroseconds(s2);
  Serial.print("\tcl\t");
  Serial.print(s1);
  scl.writeMicroseconds(s1);
  Serial.print("\tcr\t");
  Serial.print(s2);
  scr.writeMicroseconds(s2);
  Serial.print("\tbl\t");
  Serial.print(s1);
  sbl.writeMicroseconds(s1);
  Serial.print("\tbr\t");
  Serial.print(s2);
  sbr.writeMicroseconds(s2);
  Serial.println("");

    
}
