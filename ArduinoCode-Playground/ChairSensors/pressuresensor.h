#ifndef _PRESSURESENSOR
#define _PRESSURESENSOR

#define NUM_PSENSORS 4
#define LPF_ALPHA 0.1

int readPSensor(int PSensor);

void setupPSensor(int PSensor);

void readAllPSensors(int *PArray);

void setupPSensorLPF();

float readPSensorLPF(int PSensor, int updateVal);

void readAllPSensorsLPF(int *PArrayData, float *LPFDataOutput);

void setupAllPSensors();

#endif