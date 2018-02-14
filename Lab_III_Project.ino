//Jonny Cohen
//Arduino Project
//Lab Group III

//import libraries
#include <AFMotor.h>

//Intialize stepper motors
// STEPPER   is 32 steps with gearing ratio of 1/16
// so one rotation is requires 512 steps
AF_Stepper stepper(32, 2);
AF_DCMotor motor(2);

//Intialize sensor pins
int anglePin = A1;
int tempPin = A0;

void setup() {
  
  //Intialize the serial port
  Serial.begin(9600);
  
  //Pullup resistors
  digitalWrite(A1, HIGH);
  digitalWrite(A0, HIGH);
  
  //Set speed on motors
  stepper.setSpeed(300);
  motor.setSpeed(400); 
}

//Global variables
int angle;
int temp;

int stepPosition = 497; //starting point of the stepper
//int change;
int maxTemp;
int maxAngle;

void loop() {
  //Reset max values
  //stepPosition = maxAngle;
  int change = 0; //new
  int maxAngle = 0;
  int maxTemp = 0;
  

  
  while( angle < 836) {
    //Read temp and angle
    angle = analogRead(anglePin);
    temp = 1024 - analogRead(tempPin);
    
    //set max values
    if( temp > maxTemp) {
      maxTemp = temp;
      maxAngle = angle;
    }  
    
    motor.run(BACKWARD);
    delay(10);
  }
  
  //Command stepper to location

  
  while (angle > 145){
    
    //Read temp and angle
    angle = analogRead(anglePin);
    temp = 1024 - analogRead(tempPin);
    
    //set max values
    if( temp > maxTemp) {
      maxTemp = temp;
      maxAngle = angle;
    }      
    
    motor.run(FORWARD);
    delay(10);
  }
  
  //Stop motor from running
 
  motor.run(RELEASE);
  
  //change = ((maxAngle-stepPosition)/6); //NEEDS SCALAR maybe 2.7
  if ( maxAngle < stepPosition ) {
    delay(500);
    change = (stepPosition - maxAngle)/3;
    stepper.step(change, FORWARD, SINGLE);
    //stepPosition = (stepPosition - change * 6);
  }
  if ( maxAngle > stepPosition) {
    delay (500);
    change = (maxAngle - stepPosition)/3;
    stepper.step(change, BACKWARD, SINGLE);
    //stepPosition = (stepPosition + change * 6) ;
  }
  stepPosition = maxAngle;
  delay(100);
  // possible delay to allow for motor to change

  
}
