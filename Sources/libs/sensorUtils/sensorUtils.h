#include "../mcf5213/mcf5213.h"

#ifndef __SENSOR_UTILS__
#define __SENSOR_UTILS__

#define __IPSBAR ((volatile unsigned char*)(0x40000000))

int sat(int value, int min, int max);
int __atan2(float y, float x);
void getIMUdata(char acc[], char gyro[], char compass[]);
void filterIMUdata(char acc[], char gyro[], char compass[], int *pitch, int *roll, int *yaw);
void getAltitudeAndPressure(int *altitude, int *pressure);

#endif /* __SENSOR_UTILS__ */