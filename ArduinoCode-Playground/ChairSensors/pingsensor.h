#ifndef _PINGSENSOR_H
#define _PINGSENSOR_H

#define USENSOR_TRIG_OFFSET 2
#define USENSOR_PULS_OFFSET 3
#define NUM_USENSORS 0
#define USENSOR_TIMEOUT 6000  // in micro - determines range
#define USENSOR_DELAY 10// in millis - prevents inter sensor interfence

long readUSensor(int Usensor, int timeout);
void setupUSensor(int Usensor);
void readAllUSensors(int *UArray);
void setupAllUSensors();

#endif