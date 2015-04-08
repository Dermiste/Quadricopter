#include "sensorUtils.h"
#include "../../config.h"
#include "../spiUtils/spiUtils.h"


int sat(int value, int min, int max)
{
	int retour;
	if (value>max)	retour=max;
	else if (value < min) retour=min;
		 else retour=value;
	return (retour);
}

void getIMUdata(char acc[], char gyro[], char compass[])
{
	char buf[6];

	CSA_ON;
		SpiRead6R(ST_OUT_X_L_M, buf);

		compass[0] = buf[1];
		compass[1] = buf[3];
		compass[2] = buf[5];
	CSA_OFF;


	CSG_ON;
		SpiRead6R(ST_OUT_X_L, buf);

		gyro[0] = buf[1];
		gyro[1] = buf[3];
		gyro[2] = buf[5];	
	CSG_OFF;

	CSA_ON;
		SpiRead6R(ST_OUT_X_L, buf);

		acc[0] = buf[1];
		acc[1] = buf[3];
		acc[2] = buf[5];	
	CSA_OFF;	
}

void filterIMUdata(char acc[], char gyro[], char compass[], int *pitch, int *roll, int *yaw){
	int pitchAcc, rollAcc, yawMag;               
 	

    *pitch += 100 * gyro[0] * 3.906 * dt; // Angle around the X-axis
    *roll -= 100 * gyro[1] * 3.906 * dt;    // Angle around the Y-axis
    *yaw += 100 * gyro[2] * 3.906 * dt;

    int forceMagnitudeApprox = abs(acc[0]) + abs(acc[1]) + abs(acc[2]);
    if (forceMagnitudeApprox > 32 && forceMagnitudeApprox < 128) // 32 - 128 -- 8192 - 32768
    {

        pitchAcc = 10 * __atan2(acc[0], acc[2]); // 1 2
        *pitch = *pitch * compFilterCoef + pitchAcc * (1 - compFilterCoef);


        rollAcc = 10 * __atan2(-acc[1], acc[2]); //-0 2
        *roll = *roll * compFilterCoef + rollAcc * (1 - compFilterCoef);
    }
    yawMag = 10 * __atan2(compass[0],compass[1]);
    *yaw = *yaw * compFilterCoef + yawMag * (1 - compFilterCoef);
}

void getAltitudeAndPressure(int *altitude, int *pressure){
	char buf[6];
	float result;

	CS3_ON;
		SpiRead6R(PRESS_OUT_XL, buf);
	CS3_OFF;	

	*pressure = (unsigned char)buf[0] | ((unsigned char)buf[1] << 8) | ((unsigned char)buf[2] << 16);
	*pressure = *pressure * 100; // en Pa
	*pressure = *pressure >> 12;
	result = *pressure / 101325.0;
	
	*altitude = (1.0-pow(result,0.190284)) * 443076.9;
}

int __atan2(float y, float x){
  float z = y / x;
  int zi = abs((int)(z * 100)); 
  if ( zi < 100 ){
    if (zi > 10) 
     z = z / (1.0f + 0.28f * z * z);
   if (x < 0) {
     if (y < 0) z -= PI;
     else z += PI;
   }
  } else {
   z = (PI / 2.0f) - z / (z * z + 0.28f);
   if (y < 0) z -= PI;
  }
  z *= (180.0f / PI * 10); 
  return z;
}