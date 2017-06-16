#include "pingsensor.h"
#include <elapsedMillis.h>

#define USENSOR_TRIG_OFFSET 1
#define USENSOR_PULS_OFFSET 0
#define NUM_USENSORS 5
#define USENSOR_TIMEOUT 6000  // in micro - determines range
#define USENSOR_DELAY 10// in millis - prevents inter sensor interfence

// elapsedMillis loopTimer;
// long Usensors[3];

// //init
// void setup() 
// {
//   // setup serial
//   Serial.begin(9600); 

//   // setup Usensors
//   for(int s = 0; s < 3; s++)
//   {
//     setupUSensor(s+1);
//   }

//   delay(500);
//   Serial.println("Init Done");
// }

// // mainloop
// void loop()
// { // for constant data rate
//   loopTimer = 0;

//   // for each Usensor
//   for(int s = 0; s < 3; s++)
//   {
//     // read Usensor
//     Usensors[s] = readUSensor(s+1, USENSOR_TIMEOUT);
//     delay(USENSOR_DELAY); // prevents inter Usensor interferance
//   }

//   // pause for timer expiration
//   while(loopTimer < 50);

//     Serial.println(String(Usensors[0])+","+String(Usensors[1])+","+String(Usensors[2]));

// }



long readUSensor(int Usensor, int timeout)
{
  digitalWrite(Usensor*2 + USENSOR_TRIG_OFFSET, HIGH);
  delayMicroseconds(10);
  digitalWrite(Usensor*2 + USENSOR_TRIG_OFFSET, LOW);
  return pulseIn(Usensor*2 + USENSOR_PULS_OFFSET, HIGH, timeout);
}

void setupUSensor(int Usensor)
{
  pinMode(Usensor*2 + USENSOR_TRIG_OFFSET, OUTPUT);
  digitalWrite(Usensor*2 + USENSOR_TRIG_OFFSET, LOW);
  pinMode(Usensor*2 + USENSOR_PULS_OFFSET, INPUT);
}

void readAllUSensors(int *UArray)
{
  for(int s = 0; s < NUM_USENSORS; s++)
  {
    *UArray = readUSensor(i);
    UArray++;
  }
}

void setupAllUSensors()
{
  for(int s = 0; s < NUM_USENSORS; s++)
  {
    setupUSensor(s);
  }
}

