#ifndef _PINGSENSOR_H
#define _PINGSENSOR_H

#define USENSOR_TRIG_OFFSET 1
#define USENSOR_PULS_OFFSET 0
#define NUM_USENSORS 5
#define USENSOR_TIMEOUT 6000  // in micro - determines range
#define USENSOR_DELAY 10// in millis - prevents inter sensor interfence

long readUSensor(int Usensor, int timeout);
void setupUSensor(int Usensor);
void readAllUSensors(int *UArray);
void setupAllPSensors();

#endif