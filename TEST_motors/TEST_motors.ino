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


void setup()
{
//Set the PIN Modes
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinAIN2, OUTPUT);

  pinMode(pinPWMB, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);

  pinMode(pinSTBY, OUTPUT);

}

void loop()
{
 
  //Drive both motors CW, full speed
  motorDrive(motor1, turnCW, 255);
  motorDrive(motor2, turnCW, 255);
 
  //Keep driving for 2 secs
  delay(2000);

  motorBrake(1);
  motorBrake(0);
  delay(1000);
  
    //Drive both motors CW, full speed
  motorDrive(motor1, turnCCW, 255);
  motorDrive(motor2, turnCCW, 255);

    //Keep driving for 2 secs
  delay(2000);

    motorBrake(1);
    motorBrake(0);
  delay(1000);

//  wigglePins();

}

void wigglePins()
{
  digitalWrite(pinAIN1, HIGH);
  digitalWrite(pinAIN2, HIGH);
  digitalWrite(pinBIN1, HIGH);
  digitalWrite(pinBIN2, HIGH);
  analogWrite(pinPWMA, 255);
  analogWrite(pinPWMB, 255);
  digitalWrite(pinSTBY, HIGH);
  delay(2000);
  
  digitalWrite(pinAIN1, LOW);
  digitalWrite(pinAIN2, LOW);
  digitalWrite(pinBIN1, LOW);
  digitalWrite(pinBIN2, LOW);
  analogWrite(pinPWMA, 0);
  analogWrite(pinPWMB, 0);
  digitalWrite(pinSTBY, LOW);
  delay(2000);
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
