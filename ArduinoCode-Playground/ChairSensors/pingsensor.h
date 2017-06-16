#ifndef _PINGSENSOR_H
#define _PINGSENSOR_H

long readUSensor(int Usensor, int timeout);
void setupUSensor(int Usensor);
void readAllUSensors(int *UArray);

#endif