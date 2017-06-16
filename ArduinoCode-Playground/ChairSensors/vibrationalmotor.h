#ifndef _VIBRATIONALMOTOR
#define _VIBRATIONALMOTOR

#define PERIOD 1000 // usec
// #define BUZZTIME 10000//total time that the thing is cycling/vibrating in ms ( = 10 seconds here) 
#define MOTORPIN 13 //pin for the motor is 13 

void runMotorPWM(int dutyCycle, int onTime);

void motorOn();

void motorOff();

void setupMotor();

#endif