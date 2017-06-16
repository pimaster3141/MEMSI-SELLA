#include "pressuresensor.h"
#include "pingsensor.h"

#define DUMP_MODE 1
#define PREDICT_MODE 0

int pressureBoundaryMap [NUM_PSENSORS] = {0, 0, 0, 0}; //NUM_PSENSORS = 4
int ultrasoundBoundaryMap [NUM_USENSORS] = {0, 0, 0, 0}; //NUM_USENSORS = 5

void setup()
{
	Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  setupAllPSensors();
  setupAllUSensors();
  //pinMode(LEDpin, OUTPUT);
}

void loop()
{
    int* pPressureSensorArray;
    float* pLpfPressureSensorArray;
    int* pUltrasoundArray;    
    
    readAllPSensorsLPF(pPressureSensorArray, pLpfPressureSensorArray);
    readAllUSensors(pUltrasoundArray);

#if DUMP_MODE:
    //iterate through the LPF Pressure Array and Ultrasound Arrays
    for(int i=0; i<NUM_PSENSORS; i++) {
      Serial.print(pLpfPressureSensorArray[i]);
    }
    Serial.println("");

    for(int i=0; i<NUM_USENSORS; i++) {
      Serial.print(pUltrasoundArray[i]);
    }
    Serial.println("");
#endif

#if PREDICT_MODE:
    /*
    for(int i=0; i<NUM_PSENSORS; i++) {
      if (pLpfPressureSensorArray[i] > pressureBoundaryMap) {

      }
    }*/   

    for(int i=0; i<NUM_USENSORS; i++) {
      if (pUltrasoundArray[i] > ultrasoundBoundaryMap[i]) {
        Serial.println("BAD POSTURE");
      } else {
        Serial.println("GOOD POSTURE");
      }
    }
#endif
    
}

