#include "imuUtils.h"

int sat(int value, int min, int max)
{
	int retour;
	if (value>max)	retour=max;
	else if (value < min) retour=min;
		 else retour=value;
	return (retour);
}

void _getInertie(char tabInertie[], char bufGyroOld[])
{
	char bufAcc[6],bufGyro[6];

	unsigned char ad, datawrite, dataread;
	unsigned char gyro_value,acc_value;

	double floatX,floatY;
//lecture des donnees
	CSA_ON;
	SpiRead6R(bufAcc);
	CSA_OFF;
	CSG_ON;
	SpiRead6R(bufGyro);
	CSG_OFF;
}