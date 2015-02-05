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

//Calcul de l'assiette. Attention : les axes X et Y sont echanges par raport au Gyro. Coup de chance, ceci signifie que
//on recupere sur AY une acc quand on tourne AUTOUR de l'axe Y (l'acc est dans la direction X)
//Donc, pour le calcul de Theta, on aurait normalement l'info d'acc de l'axe X qui nous donne l'angle autour de Y
//mais ici c'est l'info autour de l'AccY qui nous donne l'angle autour de Y
//Lorsque le Gyro donne une dTheta >0, l'inclinaison est >0 aussi (encore un coup de chance)
//l'axe Z sert uniquement à déterminer une inversion du vol, il faut en tenir compte après si on veut tester ceci
//Theta=arcsin(mesure/g) et -2g<plage mesure<2g => normalisation en divisant par 64 puis calcul flotant
	if(bufAcc[1]>64) bufAcc[1]=64;	//tronquer AccX à +-1g pour calcul assiette
	else if (bufAcc[1]<-64) bufAcc[1]=-64;
	if(bufAcc[3]>64) bufAcc[3]=64;	//tronquer AccY à +-1g pour calcul assiette
	else if (bufAcc[3]<-64) bufAcc[3]=-64;

	//floatX = asin(bufAcc[1]/64.0);
	//floatY = asin(bufAcc[3]/64.0);

	tabInertie[0] = (char)(floatX*180/PI);//	-90<result<90 
	tabInertie[1] = (char)(floatY*180/PI);//	-90<result<90 
	tabInertie[2] = bufAcc[5];	//Acc Z en brut : utile uniquement pour le signe
	
//Recuperation des vitesses angulaires
	tabInertie[3]=bufGyro[1];	//dThetaX MSB
	tabInertie[4]=bufGyro[3];	//dThetaY MSB
	tabInertie[5]=bufGyro[5];	//dThetaZ MSB
	
//Calcul des accelerations angulaires
	//On considère que la soustraction ne peut pas generer de debdt (par exemple 125 - -6=131)
	//c'est a dire que la variation ne peut pas exceder 128 entre 2 echantillons
	tabInertie[6]=bufGyro[1]-bufGyroOld[1]; //d²ThetaX=dThetaX-dThetaXOld
	tabInertie[7]=bufGyro[3]-bufGyroOld[3];
	tabInertie[8]=bufGyro[5]-bufGyroOld[5];

	bufGyroOld[1]=bufGyro[1];
	bufGyroOld[3]=bufGyro[3];
	bufGyroOld[5]=bufGyro[5];
}