/* Projet : Quadricopter
fichier : CentInertielletest.c
Objet : fournit sur les 3 axes : inclinaison, vitesse angulaire, acc angulaire (Theta, dTheta, d²Theta)
		Inclus une fonction main pour le test.
		Il faudrait ajouter une sortie des données pour tracer des courbes et carac les capteurs
autheur : VG
Version : 1.0 - 25-06-2013
*/

#include "stdio.h"
#include "main.h"

#include "libs/spiUtils/spiUtils.h"
#include "libs/mcf5213/mcf5213.h"

#include <math.h>


#define WHO_AM_I 0x0F
//Registres accelero LIS331 et Gyro L3G4200
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

#define PI 3.141592654

//Macros pour SPI	
//CS Gyro sur PUA3
#define	CSG_ON MCF_GPIO_CLRUA=0xF7 		// Activation du CS gyro
#define	CSG_OFF MCF_GPIO_SETUA=0x08 	// DeActivation du CS gyro
//CS Acc sur PQS4
#define	CSA_ON MCF_GPIO_CLRQS=0xEF 		// Activation du CS Acc
#define	CSA_OFF MCF_GPIO_SETQS=0x10		// DeActivation du CS Acc

//Macros pour SPI	
//CS Gyro sur PUA3
//#define	CSG_ON MCF_GPIO_CLRUA=0xF7 		// Activation du CS gyro
//#define	CSG_OFF MCF_GPIO_SETUA=0x08 	// DeActivation du CS gyro
//CS Acc sur PQS4
//#define	CSA_ON MCF_GPIO_CLRQS=0xEF 		// Activation du CS Acc
//#define	CSA_OFF MCF_GPIO_SETQS=0x10		// DeActivation du CS Acc

//Variables globales
char tabInertie[9];
	//contenu tabInertie : ThetaX, ThetaY, AccZ, dThetaX,dThetaY,dThetaZ,D²ThetaX,d²ThetaY,d²ThetaZ
char bufGyroOld[6];	//pour calcul derivee vitesse angulaire (acceleration angulaire)
int __errno=0;	//pour gestion messages d'erreur des fcts asin, acos de libm.a

int testMode = 0;
int totalData = 10;
int dataTraced = 0;


void GetInertie(void);


void GetInertie(void)
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

	floatX = asin(bufAcc[1]/64.0);
	floatY = asin(bufAcc[3]/64.0);

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
   
int main (void)
{	
	char temp;
	unsigned int i;
	
	printf("Test Centrale inertielle\n");
	
	Init_spi();			//init IOs liees au bus SPI
	if(Init_AccGyro()!=0)	//Init des composants
		printf("Erreur d'init Acc ou Gyro\n");
	//RAZ de tabInertieOld pour premier calcul de derivee
	for(i=0;i<6;i++)
		bufGyroOld[i]=0;
		
//lecture temp sur Gyro :	
	CSG_ON;
	temp=SpiRead8(OUT_TEMP);
	CSG_OFF;
	printf("TempGyro=%d\n",temp );
	printf("taper touche\n\n");
	getch();
	
	while(1)
	{
		/*GetInertie();	//retourne dans tabInertie les valeurs
		if (testMode){
			putchar(0xFF); // start bit
			putchar(tabInertie[0]);
			putchar(tabInertie[1]);
			putchar(tabInertie[2]);
			putchar(tabInertie[3]);
			putchar(tabInertie[4]);
			putchar(tabInertie[5]);
			putchar(tabInertie[6]);
			putchar(tabInertie[7]);
			putchar(tabInertie[8]);
			putchar(0xF0); // end bit
			dataTraced += 1;
			if (dataTraced == totalData){
				testMode = 0;
			}
		} else {
			printf("ThetaX=%d    ", tabInertie[0]);
			printf("ThetaY=%d    ", tabInertie[1]);
			printf("AccZ=%d  \n", tabInertie[2]);
			printf("VAX=%d       ", tabInertie[3]);
			printf("VAY=%d       ", tabInertie[4]);
			printf("VAZ=%d  \n", tabInertie[5]);
			printf("AAX=%d       ", tabInertie[6]);
			printf("AAY=%d       ", tabInertie[7]);
			printf("AAZ=%d  \n", tabInertie[8]);			
		}*/

		//printf("\033[3A");		//remonter curseur
		
		//for(i=0;i<3000000;i++)
		//{}
		
	

		char choix, i;
		if (kbhit())
			{
				choix = getch();	//lire derniere touche appuyee
				switch (choix)
				{
				case 27:		// touche Esc
					printf("\n\n\n\n");	//redecendre curseur
					return(0);
					break;
				case 116: //t
					testMode = !testMode;
					break;
				case 'a': //t
					out_char('b');
					//printf("Hello!");	
					break;		
				case 'b':
					GetInertie();
					out_char(tabInertie[0]);
					out_char(tabInertie[1]);
					out_char(tabInertie[2]);
					out_char(tabInertie[3]);
					out_char(tabInertie[4]);
					out_char(tabInertie[5]);
					out_char(tabInertie[6]);
					out_char(tabInertie[7]);
					out_char(tabInertie[8]);
				break;		

				case 'c':
					GetInertie();
					printf("ThetaX=%d    ", tabInertie[0]);
					printf("ThetaY=%d    ", tabInertie[1]);
					printf("AccZ=%d  \n", tabInertie[2]);
					printf("VAX=%d       ", tabInertie[3]);
					printf("VAY=%d       ", tabInertie[4]);
					printf("VAZ=%d  \n", tabInertie[5]);
					printf("AAX=%d       ", tabInertie[6]);
					printf("AAY=%d       ", tabInertie[7]);
					printf("AAZ=%d  \n", tabInertie[8]);
				break;	
				}
			}
	}		
}

//*****FONCTIONS DE GESTION DU DIALOGUE SPI*****//
/*char Init_AccGyro (void)
{
	unsigned char gyro_value, acc_value;
//config Gyro CTRL_REG1:
	//ODR=400Hz, Cut-off=110Hz => DR+BW="1011"
	//Tous les axes activés : PD=1, Zen=1, Yen=1, Xen=1
	CSG_ON;
	SpiWrite8(CTRL_REG1,0xBF);//0b1011.1111
	CSG_OFF;
	
	//CTRLREG2:
	//normal mode :0000
	//filtre passe haut =0,1Hz, avec ODR400Hz : 1000
	CSG_ON;
	SpiWrite8(CTRL_REG2,0x08);
	CSG_OFF;
	
	//CTRLREG3 : config defaut =0
	//CTRLREG4 : config FS1-FS0 =01 pour sensibilite=500deg/s (=> Quantum=17,5mdps)
	CSG_ON;
	SpiWrite8(CTRL_REG4,0x10);
	CSG_OFF;
	
	//CTRLREG5 : HPF ?
	CSG_ON;
	SpiWrite8(CTRL_REG5,0x00);//HPF enable : 0x10 
	CSG_OFF;
	
//Config Acc CTRL_REG1:
	CSA_ON;
	SpiWrite8(CTRL_REG1,0x37);	//Mode normal, data rate 400Hz, en all axis
	CSA_OFF;
	//CTRL_REG2 : default value : Filters bypass
	//CTRLREG3: default VAlue, pas d'ITS
	//CTRLREG4 : default value : full scale =+-2g, /!\ continuous update MSB LSB
	//CTRLREG5 : default value : sleep to wake disabled
	CSA_ON;
	acc_value=SpiRead8(WHO_AM_I);
	CSA_OFF;
	CSG_ON;
	gyro_value=SpiRead8(WHO_AM_I);
	CSG_OFF;
	//printf("Who am I ACC=%d\tWho am I Gyro=%d\n",acc_value,gyro_value);
	if ((acc_value != 0x32) || (gyro_value !=0xd3))
		return(-1);
	else return(0);
}*/
