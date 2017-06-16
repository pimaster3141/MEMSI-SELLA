#ifndef _PRESSURESENSOR
#define _PRESSURESENSOR

int readPSensor(int PSensor);

void setupPSensor(int PSensor);

void readAllPSensors(int *PArray);

void setupPSensorLPF();

float readPSensorLPF(int PSensor, int updateVal);

void readAllPSensorsLPF(int *PArrayData, float *LPFDataOutput);

#endif