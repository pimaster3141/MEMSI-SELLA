#include "pressuresensor.h"
#include <elapsedMillis.h>

#define NUM_PSENSORS 4
#define LPF_ALPHA 0.1

elapsedMillis loopTimer;
float PSensorLPFStates[NUM_PSENSORS];

// float PSensors[NUM_PSENSORS];
// int PSensorsRAW[NUM_PSENSORS];

// //init
// void setup() 
// {
//   // setup serial
//   Serial.begin(9600); 

//   // setup PSensors
//   for(int s = 0; s < NUM_PSENSORS; s++)
//   {
//     setupPSensor(s);
//   }

//   setupPSensorLPF();

//   delay(500);
//   Serial.println("Init Done");
// }

// // mainloop
// void loop()
// { // for constant data rate
//   loopTimer = 0;

//   // for each PSensor
//   // for(int s = 0; s < NUM_PSENSORS; s++)
//   // {
//   //   // read PSensor
//   //   PSensors[s] = readPSensor(s+1);
//   //   //delay(PSensor_DELAY); // prevents inter PSensor interferance
//   // }

//   readAllPSensors(PSensorsRAW);
//   readAllPSensorsLPF(PSensorsRAW, PSensors);

//   // pause for timer expiration
//   while(loopTimer < 10);
//   for(int s = 0; s < NUM_PSENSORS; s++)
//   {
//     Serial.print(String(PSensors[s]) + ",");
//     //Serial.println(String(PSensors[0])+","+String(PSensors[1])+","+String(PSensors[2])+","+String(PSensors[3]));
//   }
//   Serial.println();

// }


int readPSensor(int PSensor)
{
  return analogRead(PSensor);    
}

void setupPSensor(int PSensor)
{
  return;
}

void readAllPSensors(int *PArray)
{
  for(int i = 0; i < NUM_PSENSORS; i++)
  {
    *PArray = readPSensor(i);
    PArray++;
  }
}

void setupPSensorLPF()
{
  for(int i = 0; i < NUM_PSENSORS; i++)
  {
    PSensorLPFStates[i] = readPSensor(i);
  }
}

float readPSensorLPF(int PSensor, int updateVal)
{
  updateVal = float(updateVal);
  PSensorLPFStates[PSensor] = updateVal*LPF_ALPHA + PSensorLPFStates[PSensor]*(1-LPF_ALPHA);
  return PSensorLPFStates[PSensor];
}

void readAllPSensorsLPF(int *PArrayData, float *LPFDataOutput)
{
  for(int i = 0; i < NUM_PSENSORS; i++)
  {
    *LPFDataOutput = readPSensorLPF(i, *PArrayData);
    LPFDataOutput++;
    PArrayData++;
  }
}

