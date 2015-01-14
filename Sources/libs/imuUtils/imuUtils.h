#include "../mcf5213/mcf5213.h"

#ifndef __IMU_UTILS__
#define __IMU_UTILS__

#define __IPSBAR ((volatile unsigned char*)(0x40000000))

#define	CSG_ON MCF_GPIO_CLRUA=0xF7 		// Activation du CS gyro
#define	CSG_OFF MCF_GPIO_SETUA=0x08 	// DeActivation du CS gyro
//CS Acc sur PQS4
#define	CSA_ON MCF_GPIO_CLRQS=0xEF 		// Activation du CS Acc
#define	CSA_OFF MCF_GPIO_SETQS=0x10		// DeActivation du CS Acc

#define PI 3.141592654

int sat(int value, int min, int max);
void getInertie(char tabInertie[], char bufGyroOld[]);

#endif /* __IMU_UTILS__ */