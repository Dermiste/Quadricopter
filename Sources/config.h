#ifndef __CONFIG__
#define __CONFIG__

#define PI 3.141592654

#define dt 0.01
#define freq 100

#define timeConstant 0.5
#define compFilterCoef timeConstant / (timeConstant + dt)//0.9782;

#define ACCELEROMETER_SENSITIVITY 32.0 
#define GYROSCOPE_SENSITIVITY 17.5	

#define PRESSURE_REF 101325
#define PRESSURE_POW 0.190284
#define PRESSURE_MULT 44307.69

#endif /* __CONFIG__ */