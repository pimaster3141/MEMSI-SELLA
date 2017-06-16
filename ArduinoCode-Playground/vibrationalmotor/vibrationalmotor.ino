/*
THIS FILE HAS BEEN FINALIZED. DO NOT EDIT. FIND THE vibrationalmotor.h AND
vibrationalmotor.c FILES



8888888888888888888888888888888888888888888888888
*/









//#define FREQ 10000 //1-10 khz frequency for PWM
#define PERIOD 1000 // usec
// #define BUZZTIME 10000//total time that the thing is cycling/vibrating in ms ( = 10 seconds here) 
#define MOTORPIN 13 //pin for the motor is 13 
//yay posture pioneers
//in general use defines for hardware specs that don't need to be updated real time by the software, saves memory

//int dutyCycle = 25 //change between 1-100 to change intensity, change this to be a parameter 

// #import 


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


// //start helper functions

// void overallLoop(){
  
// }

// void runMotorBasic(int timeDelay){
//   digitalWrite(MOTORPIN, HIGH);
//   delayMicroseconds(timeDelay);
//   // digitalWrite(MOTORPIN, LOW);
// }

// void motorOff(int timeDelay){
//   digitalWrite(MOTORPIN, LOW);
//   delayMicroseconds(timeDelay);
// }


//troubleshoot this later
void runMotorPWM(int dutyCycle, int onTime){ //runs motor for msec onTime 
  long cycles = long(onTime) * 1000 / PERIOD;

  if(dutyCycle > 100)
    dutyCycle = 100;
  if(dutyCycle < 0)
    dutyCycle = 0;

  int tON = (PERIOD * dutyCycle) / 100;
  int tOFF = PERIOD - tON;

  for (int i = 0; i < cycles; i++){
    //turn on high state for 1st part of the cycle aka for the % duty cycle
    // runMotorBasic((dutyCycle/100)*PERIOD); //time on in cycle
    // motorOff(PERIOD - dutyCycle/100*PERIOD); //time off in cycle 
    digitalWrite(MOTORPIN, HIGH);
    delayMicroseconds(tON);
    digitalWrite(MOTORPIN, LOW);
    delayMicroseconds(tOFF);
  }

}


// void runAlert(){
//   runMotorBasic(3000); 
//   delay(100);
// }

// void runAlertPWM(int intensity){
//   runMotorPWM(intensity); 
//   delay(100);
// }

 
void loop()
{
  for(int i = 0; i < 5; i++)
  {
    runMotorPWM((i+1)*20, 2000);
    delay(1000);
  }
  runMotorPWM(100, 1000);

  // runMotorBasic(3000); 
  // delay(10000);
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

