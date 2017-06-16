#include "pingsensor.h"
#include "pressuresensor.h"
#include "vibrationalmotor.h"

#define SENSOR_REFRESH_PERIOD 50 // msec
#define NUM_SAMPLES 20
#define PSENSOR_ERROR_THRESHOLD 1000
#define USENSOR_ERROR_THRESHOLD 1000
#define BAD_COUNTER_THRESHOLD 10  

#define BUTTON_PORT 19

float PSensorCalibration[NUM_PSENSORS];
float USensorCalibration[NUM_USENSORS];


void setupSensors()
{
  setupAllPSensors();
  setupAllUSensors();
}

void calibratePosture()
{
  setupPSensorLPF();
  int PSensorsRAW[NUM_PSENSORS];
  float PSensors[NUM_PSENSORS];
  int USensors[NUM_USENSORS];

  for(int i = 0; i < NUM_SAMPLES; i++)
  {
    readAllPSensors(PSensorsRAW);
    readAllUSensors(USensors);
    readAllPSensorsLPF(PSensorsRAW, PSensors);

    for(int j = 0; j < NUM_PSENSORS; j++)
    {
      PSensorCalibration[i] = PSensorCalibration[i] + (PSensors[i]/NUM_SAMPLES);
    }

    for(int j = 0; j < NUM_USENSORS; j++)
    {
      USensorCalibration[i] = USensorCalibration[i] + (float(USensors[i])/NUM_SAMPLES);
    }
  }
}

bool goodPosture()
{
  setupPSensorLPF();
  int PSensorsRAW[NUM_PSENSORS];
  float PSensors[NUM_PSENSORS];
  int USensors[NUM_USENSORS];

  readAllPSensors(PSensorsRAW);
  readAllUSensors(USensors);
  readAllPSensorsLPF(PSensorsRAW, PSensors);

  long PSensorError = 0;
  long USensorError = 0;

  for(int i = 0; i < NUM_PSENSORS; i++)
  {
    long temp = PSensors[i] - PSensorCalibration[i];
    if(temp < 0)
      temp = -temp;
    PSensorError = PSensorError + temp;
  }

  for(int i = 0; i < NUM_USENSORS; i++)
  {
    long temp = USensors[i] - USensorCalibration[i];
    if(temp < 0)
      temp = -temp;
    USensorError = USensorError + temp;
  }

  if(PSensorError > PSENSOR_ERROR_THRESHOLD || USensorError > USENSOR_ERROR_THRESHOLD)
    return false;
  return true;
}

void setup()
{
  pinMode(BUTTON_PORT, INPUT);
  delay(50);
  if(digitalRead(BUTTON_PORT) == 1)
    debugMode();

  setupMotor();
  setupSensors();
  delay(100);

  while(digitalRead(BUTTON_PORT) == 0);

  calibratePosture();
}

void loop()
{
  int badCounter = 0;

  while(true)
  {
    if(digitalRead(BUTTON_PORT) == 1)
    {
      calibratePosture();
      break;
    }

    if(!goodPosture())
    {
      if(badCounter > BAD_COUNTER_THRESHOLD)
        motorOn();

      else
        badCounter = badCounter + 1;
    }

    else
    {
      motorOff();
      badCounter = 0;
    }

  }
}

void debugMode()
{
  Serial.begin(9600);
  setupSensors(); 
  delay(500);
  Serial.println("DEBUG MODE");

  setupPSensorLPF();
  int PSensorsRAW[NUM_PSENSORS];
  float PSensors[NUM_PSENSORS];
  int USensors[NUM_USENSORS];

  while(true)
  {
    readAllPSensors(PSensorsRAW);
    readAllUSensors(USensors);
    readAllPSensorsLPF(PSensorsRAW, PSensors);


    Serial.print("Pressure:");
    for(int s = 0; s < NUM_PSENSORS; s++)
    {
      Serial.print(String(PSensors[s]) + ",");
    }
    Serial.println();

    Serial.print("Ping:");
    for(int s = 0; s < NUM_USENSORS; s++)
    {
      Serial.print(String(USensors[s]) + ",");
    }
    Serial.println();
    Serial.println();

  }
}
