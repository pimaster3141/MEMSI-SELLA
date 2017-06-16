#include "pingsensor.h"
#include "pressuresensor.h"
#include "vibrationalmotor.h"
#include <elapsedMillis.h>

#define SENSOR_REFRESH_PERIOD 50 // msec
#define NUM_SAMPLES 20
#define PSENSOR_ERROR_THRESHOLD 180
#define USENSOR_ERROR_THRESHOLD 1000
#define BAD_COUNTER_THRESHOLD 12  

#define BUTTON_PORT 12

float PSensorCalibration[NUM_PSENSORS];
float USensorCalibration[NUM_USENSORS];


void setupSensors()
{
  setupAllPSensors();
  setupAllUSensors();
}

void calibratePosture()
{
  Serial.println("Calibrating...");
  motorOff();
  setupPSensorLPF();
  int PSensorsRAW[NUM_PSENSORS];
  float PSensors[NUM_PSENSORS];
  int USensors[NUM_USENSORS];
  elapsedMillis timeout = 0;

  for(int j = 0; j < NUM_PSENSORS; j++)
  {
    PSensorCalibration[j] = 0;
  }

  for(int j = 0; j < NUM_USENSORS; j++)
  {
    USensorCalibration[j] = 0;
  }

  for(int i = 0; i < NUM_SAMPLES; i++)
  {
    timeout = 0;
    readAllPSensors(PSensorsRAW);
    readAllUSensors(USensors);
    readAllPSensorsLPF(PSensorsRAW, PSensors);

    for(int j = 0; j < NUM_PSENSORS; j++)
    {
      PSensorCalibration[j] = PSensorCalibration[j] + (PSensors[j]/NUM_SAMPLES);
    }

    for(int j = 0; j < NUM_USENSORS; j++)
    {
      USensorCalibration[j] = USensorCalibration[i] + (float(USensors[i])/NUM_SAMPLES);
    }

    while(timeout < SENSOR_REFRESH_PERIOD);
    // Serial.println(i);
  }

  // Serial.println("here!");
  delay(500);
  for(int i = 0; i < NUM_PSENSORS; i++)
    Serial.print(String(PSensorCalibration[i])+", ");
  // Serial.println();

  for(int i = 0; i < NUM_PSENSORS; i++)
    Serial.print(String(PSensors[i])+", ");
  // Serial.println();
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

  // Serial.println(PSensorError);

  if(PSensorError > PSENSOR_ERROR_THRESHOLD || USensorError > USENSOR_ERROR_THRESHOLD)
    return false;
  return true;
}

void setup()
{

  Serial.begin(9600);
  Serial.println("AT+INIT");
  delay(200);
  Serial.println("STARTUP");
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
  elapsedMillis timeout = 0;

  // while(true)
  // {
  //   motorOn();
  //   delay(1000);
  //   motorOff();
  //   delay(1000);
  // }

  while(true)
  {
    timeout = 0;
    if(digitalRead(BUTTON_PORT) == 1)
    {
      calibratePosture();
      break;
    }

    if(!goodPosture())
    {
      if(badCounter > BAD_COUNTER_THRESHOLD)
      {

        // Serial.println("BAD");
        Serial.write(0);
        motorOn();
      }

      else
        badCounter = badCounter + 1;
    }

    else
    {
      motorOff();
      badCounter = 0;
      // Serial.println("GOOD");
      Serial.write(1);
    }

    while(timeout < SENSOR_REFRESH_PERIOD);
  }
}

void debugMode()
{
  Serial.begin(9600);
  setupSensors(); 
  delay(500);
  // Serial.println("DEBUG MODE");

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
    // Serial.println();

    Serial.print("Ping:");
    for(int s = 0; s < NUM_USENSORS; s++)
    {
      Serial.print(String(USensors[s]) + ",");
    }
    // Serial.println();

    Serial.print("Button:");
    Serial.print(digitalRead(BUTTON_PORT));
    // Serial.println();
    // Serial.println();

    delay(200);

  }
}
