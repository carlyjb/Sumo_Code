#include <ZumoMotors.h>

#define TURN_SPEED 125
#define DRIVE_SPEED 400
#define REVERSE_TIME 200
#define PING_RANGE 50       //centimeters
#define TURN_DURATION 500
#define LIGHT_THRESH 200 // greater than = black

/*
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

ZumoMotors motors;

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
const int echoPin = A7; 

int Left_Light_Pin = A6;     // analog 6
int Right_Light_Pin = A0;    // analog 0

// light sensors
float QRE_Value_L = 0;
float QRE_Value_R = 0;
long ObjectDistance;

// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, inches, cm;

int rightTurnCount, leftTurnCount;




void setup() 
{ // put your setup code here, to run once:
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinAIN2, OUTPUT);

  pinMode(pinPWMB, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);

  pinMode(pinSTBY, OUTPUT);

  rightTurnCount = 0;
  leftTurnCount = 0;

  delay(5010);  //wait 5 seconds at beginning of match  
}



void loop() 
{ // put your main code here, to run repeatedly:
  QRE_Value_L = analogRead(Left_Light_Pin);
  QRE_Value_R = analogRead(Right_Light_Pin);

  ObjectDistance = GetPingDistance();
  if(ObjectDistance < 6)
  {
    driveForward();
  }
  else
  {
    if (rightTurnCount < TURN_DURATION)
    {
      turnRight();
      rightTurnCount++;
    }
    else if (leftTurnCount < TURN_DURATION)
    {
      turnLeft();
      leftTurnCount++;
    }
    else
    {
      rightTurnCount = 0;
      leftTurnCount = 0;
      turnLeft();
      leftTurnCount++;
    }
  }
}

void Ping(int TimeLength)
{
  int MaxTime = TimeLength/10;
  int i = 0;
  while(i < TimeLength)
  {
    i++;
    long ObjectDistance = GetPingDistance();
  }
}

void driveForward()
{
    motorDrive(motor1, turnCCW, 255);
    motorDrive(motor2, turnCCW, 255);
}

void driveBackward()
{
    motorDrive(motor1, turnCW, 255);
    motorDrive(motor2, turnCW, 255);
}

void turnRight()
{
  motorDrive(motor1, turnCW, 255);
  motorDrive(motor2, turnCCW, 255);
}

void turnLeft()
{
  motorDrive(motor1, turnCCW, 255);
  motorDrive(motor2, turnCW, 255);
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
/* This "Short Brake"s the specified motor, by setting speed to zero */

  if (motorNumber == motor1)
    analogWrite(pinPWMA, 0);
  else
    analogWrite(pinPWMB, 0);
}

void motorStop(boolean motorNumber)
{
  /*  This stops the specified motor by setting both IN pins to LOW */
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
  /*  This puts the motors into Standby Mode */
  digitalWrite(pinSTBY, LOW);
}

long GetPingDistance()
{
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
  // inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  delay(3);       // function delays 10ms
  return(cm);
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

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

