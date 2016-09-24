/* HC-SR04 Sensor
   https://www.dealextreme.com/p/hc-sr04-ultrasonic-sensor-distance-measuring-module-133696
  
   This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.
     
   The circuit:
  * VCC connection of the sensor attached to +5V
  * GND connection of the sensor attached to ground
  * TRIG connection of the sensor attached to digital pin 2
  * ECHO connection of the sensor attached to digital pin 4


   Original code for Ping))) example was created by David A. Mellis
   Adapted for HC-SR04 by Tautvidas Sipavicius

   This example code is in the public domain.
 */

 /*
Sample Code to run the Sparkfun TB6612FNG 1A Dual Motor Driver using Arduino UNO R3

This code conducts a few simple manoeuvres to illustrate the functions:
  - motorDrive(motorNumber, motorDirection, motorSpeed)
  - motorBrake(motorNumber)
  - motorStop(motorNumber)
  - motorsStandby

Connections:
- Pin 9 ---> PWMA
- Pin 12 ---> AIN2
- Pin 13 ---> AIN1
- Pin 8 ---> STBY
- Pin 5 ---> BIN1
- Pin 4 ---> BIN2
- Pin 10 ---> PWMB

- Motor 1: A01 and A02
- Motor 2: B01 and B02

*/

//Define the Pins

//Motor 1
int pinAIN1 = 13; //Direction
int pinAIN2 = 12; //Direction
int pinPWMA = 9; //Speed

//Motor 2
int pinBIN1 = 5; //Direction
int pinBIN2 = 4; //Direction
int pinPWMB = 10; //Speed

//Standby
int pinSTBY = 8;

//Constants to help remember the parameters
static boolean turnCW = 0;  //for motorDrive function
static boolean turnCCW = 1; //for motorDrive function
static boolean motor1 = 0;  //for motorDrive, motorStop, motorBrake functions
static boolean motor2 = 1;  //for motorDrive, motorStop, motorBrake functions


const int trigPin = A4; 
const int echoPin = A5; 

const int ledPin = 13;

void setup() {

  pinMode(13, OUTPUT);

  pinMode(pinPWMA, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinAIN2, OUTPUT);

  pinMode(pinPWMB, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);

  pinMode(pinSTBY, OUTPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  analogWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  if(inches <= 5)
  {
    digitalWrite(ledPin, HIGH);
     
    //Drive both motors CW, full speed
    motorDrive(motor1, turnCW, 255);
    motorDrive(motor2, turnCW, 255);
  }
  else
  {
    digitalWrite(ledPin, LOW);

    //Drive both motors CCW, full speed
    motorDrive(motor1, turnCCW, 255);
    motorDrive(motor2, turnCCW, 255);
  }
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}


void motorDrive(boolean motorNumber, boolean motorDirection, int motorSpeed)
{
  /*
  This Drives a specified motor, in a specific direction, at a specified speed:
    - motorNumber: motor1 or motor2 ---> Motor 1 or Motor 2
    - motorDirection: turnCW or turnCCW ---> clockwise or counter-clockwise
    - motorSpeed: 0 to 255 ---> 0 = stop / 255 = fast
  */

  boolean pinIn1;  //Relates to AIN1 or BIN1 (depending on the motor number specified)

 
//Specify the Direction to turn the motor
  //Clockwise: AIN1/BIN1 = HIGH and AIN2/BIN2 = LOW
  //Counter-Clockwise: AIN1/BIN1 = LOW and AIN2/BIN2 = HIGH
  if (motorDirection == turnCW)
    pinIn1 = HIGH;
  else
    pinIn1 = LOW;

//Select the motor to turn, and set the direction and the speed
  if(motorNumber == motor1)
  {
    digitalWrite(pinAIN1, pinIn1);
    digitalWrite(pinAIN2, !pinIn1);  //This is the opposite of the AIN1
    analogWrite(pinPWMA, motorSpeed);
  }
  else
  {
    digitalWrite(pinBIN1, pinIn1);
    digitalWrite(pinBIN2, !pinIn1);  //This is the opposite of the BIN1
    analogWrite(pinPWMB, motorSpeed);
  }
   
 

//Finally , make sure STBY is disabled - pull it HIGH
  digitalWrite(pinSTBY, HIGH);

}

void motorBrake(boolean motorNumber)
{
/*
This "Short Brake"s the specified motor, by setting speed to zero
*/

  if (motorNumber == motor1)
    analogWrite(pinPWMA, 0);
  else
    analogWrite(pinPWMB, 0);
   
}


void motorStop(boolean motorNumber)
{
  /*
  This stops the specified motor by setting both IN pins to LOW
  */
  if (motorNumber == motor1) {
    digitalWrite(pinAIN1, LOW);
    digitalWrite(pinAIN2, LOW);
  }
  else
  {
    digitalWrite(pinBIN1, LOW);
    digitalWrite(pinBIN2, LOW);
  } 
}


void motorsStandby()
{
  /*
  This puts the motors into Standby Mode
  */
  digitalWrite(pinSTBY, LOW);
}
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
