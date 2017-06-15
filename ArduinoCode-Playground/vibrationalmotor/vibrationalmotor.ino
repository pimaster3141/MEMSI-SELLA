#define FREQ 10000 //1-10 khz frequency for PWM
#define PERIOD 1000 //1/freq 100 ms (100x the period gives total time) 
#define BUZZTIME 10000//total time that the thing is cycling/vibrating in ms ( = 10 seconds here) 
#define MOTORPIN 13 //pin for the motor is 13 
//yay posture pioneers
//in general use defines for hardware specs that don't need to be updated real time by the software, saves memory

//int dutyCycle = 25 //change between 1-100 to change intensity, change this to be a parameter 

#import 


//
//const int motorPin = 3;
//int requiredTime = 60*60; //get a delay time over ble from app or webapp, gives you how long until the posture 
//bool badPosture = 0; //bool to show if you have bad posture or not 
//bool stopVibrating = 0; //bool to turn off haptic feedback 
////motor can be turned off via either a switch on the side of the chair or via app
//
////need to get delayTime, badPosture bool, and offMode 


void setup()
{
pinMode(MOTORPIN,OUTPUT);


//get any bluetooth info on posture here 
}


//start helper functions

void overallLoop(){
  
}

void runMotorBasic(int timeDelay){
  digitalWrite(MOTORPIN, HIGH);
  delay(timeDelay);
  digitalWrite(MOTORPIN, LOW);
}

void motorOff(int timeDelay){
  digitalWrite(MOTORPIN, LOW);
  delay(timeDelay);
}


//troubleshoot this later
void runMotorPWM(int dutyCycle){ //runs motor for buzztime 
  for (int i = 0; i < BUZZTIME/PERIOD; i++){
    //turn on high state for 1st part of the cycle aka for the % duty cycle
    runMotorBasic((dutyCycle/100)*PERIOD); //time on in cycle
    motorOff(PERIOD - dutyCycle/100*PERIOD); //time off in cycle 
  }

}


void runAlert(){
  runMotorBasic(3000); 
  delay(100);
}

void runAlertPWM(int intensity){
  runMotorPWM(intensity); 
  delay(100);
}

 
void loop()
{

  runMotorBasic(3000); 
  delay(10000);
//  runMotorBasic(1000); 
//  motorOff(20) ; 
//  runMotorPWM(25);
//  motorOff(200);
//  runMotorPWM(75); 
//  motorOff(500); 


//if (badPosture()){
//  startTimer(){
//    
//  }
//}
//digitalWrite(motorPin, HIGH);
//delay(10000);
// 
//digitalWrite(motorPin,LOW);
//delay(10000);
}

