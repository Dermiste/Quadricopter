/* Projet : Quadricopter
fichier : 4xCopter.c
Objet : prog principal d'asservissement
autheurs : VG / J-E G-B
Version :	1.0 - 27-06-2013 Tests de base
			1.1 - 11-07-2013 Mise en route des moteurs !
*/

#include "stdio.h"
#include "main.h"
#include "libs/filters/AccFilter.h"
#include "libs/spiUtils/spiUtils.h"
#include "libs/mcf5213/mcf5213.h"
#include <math.h>

#define AX tabInertie[0]
#define AY tabInertie[1]
#define AccZ tabInertie[2]
#define VAX tabInertie[3]
#define VAY tabInertie[4]
#define VAZ tabInertie[5]
#define AAX tabInertie[6]
#define AAY tabInertie[7]
#define AAZ tabInertie[8]

#define ACCELEROMETER_SENSITIVITY 32.0 // 32.0 - 8192
#define GYROSCOPE_SENSITIVITY 17.5			
			
#define PI 3.141592654
#define M_PI 3.141592654
#define dt 0.01

// moteur1 PWMDTY7
// moteur2 PWMDTY3
// moteur3 PWMDTY5
// moteur4 PWMDTY1

#define NVECT_TMR0 (64 + 19)
#define NVECT_TMR2 (64 + 21)
#define ADR_VECT_INT0 (0x20000000 + NVECT_TMR0*4)
#define ADR_VECT_INT2 (0x20000000 + NVECT_TMR2*4)

extern void isrINT0(void);
extern void isrINT2(void);

//Variables globales
char tabInertie[9];
	//contenu tabInertie : ThetaX, ThetaY, AccZ, dThetaX,dThetaY,dThetaZ,D²ThetaX,d²ThetaY,d²ThetaZ
char bufGyroOld[6];	//pour calcul derivee vitesse angulaire (acceleration angulaire)

char gyrData[3];
char accData[3];


int __errno=0;	//pour gestion messages d'erreur des fcts asin, acos de libm.a
signed int control_r=0,control_p=0,control_y=0;
int GvX,GvY,GvZ,GaX,GaY,IGpX,IGpY;	//gains asservissement
int SumAY=0,SumAX=0;	//moyennage Angles
char MoyAX,MoyAY;	//Angles moyennes
int nirq = 0;
signed int moteur1,moteur2,moteur3,moteur4;
unsigned char PWMot1,PWMot2,PWMot3,PWMot4;

unsigned long timeClock,startTime = 0;
unsigned int initialThurst = 0;
int thrustOffset = 0;
int totalSample = 0;
unsigned int testMode = 0,shouldFinishTest = 0;


void Init_5213(void);
void Init_PWM (void);
void ComplementaryFilter(char accData[3], char gyrData[3], double *pitch, double *roll);

void GetInertie(void);

double pitch = 0,roll = 0;
signed int targetPitch = 0, targetRoll = 0;
signed int errorPitch = 0, errorRoll = 0;

char controlActivated = 0;

double compFilterCoef = 0.02;

//double PID

void actionINT0(void) {
	//unsigned int ii;
	nirq++;
	switch(nirq){
		case 1:
			initialThurst = 0;
		break;

		/*case 100:
			thrustOffset = 5;
		break;*/

		case 100:
			initialThurst = 120;
			//thrustOffset = 5;
		break;

		case 350:
			//stopTest();
			thrustOffset = 0;
			initialThurst = 0;
			MCF_DTIM0_DTMR=0x500B;
			nirq = 0;
			shouldFinishTest = 1;
		break;
	}	//printf("Occurence num. %d de TIMER1 \n", nirq);

	// Acquittement de l'interruption
	MCF_DTIM0_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

void actionINT2(void) {
	//unsigned int ii;
	timeClock += 1;
	// Acquittement de l'interruption
	MCF_DTIM2_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

int main (void)
{	
	printf("Starting ...:\n");
	char temp, choix;
	unsigned int i, gas, cpt_ech, cpt_moyAngle;
	gas = 0;
	printf("Reponse indicielle:\n");
	

/* INIT des gains*/
	GaX=1;
	GaY=1;
	GvX=2;
	GvY=2;
	GvZ=1;
	IGpX=4;	//gain 1/4
	IGpY=4;
	
/*Init des IOs*/	
	Init_5213();		//bus SPI
	Init_PWM();
	int result = Init_AccGyro();
	while(!result){	//Init des composants
		printf("Erreur d'init Acc ou Gyro, retrying ...\n");
		result = Init_AccGyro();
	}
		
//lecture temp sur Gyro :	
	CSG_ON;
	temp=SpiRead8(ST_GYRO_OUT_TEMP);
	CSG_OFF;
	//printf("TempGyro=%d\n",temp );
	//printf("taper touche\n");
	getch();
	

	while(1)
	{
		while ((MCF_DTIM3_DTER & 2)==0);//attend prochain date ech
		MCF_DTIM3_DTER = 2;				//RAZ Flag

		GetInertie();	//retourne dans tabInertie les valeurs
		ComplementaryFilter(accData,gyrData,&pitch,&roll);


        MCF_PWM_PWMDTY5 = initialThurst + thrustOffset;
        MCF_PWM_PWMDTY1 = initialThurst;


		if (controlActivated){
			errorPitch = targetPitch - (signed int)pitch;
			errorRoll = targetRoll - (signed int)roll;

			control_p = errorPitch / 2;
			
			moteur3 =  gas + control_p;
			moteur4 =  gas - control_p;

			MCF_PWM_PWMDTY5 = (unsigned char)sat(moteur3+110,100,180);
			MCF_PWM_PWMDTY1 = (unsigned char)sat(moteur4+110,100,180);	//on limite a 180 pour commencer...
			gas = 20;
		} else {
			MCF_PWM_PWMDTY5 = 120;
			MCF_PWM_PWMDTY1 = 120;
			gas = 0;
		}



		if (testMode){
			if (shouldFinishTest){
				testMode = 0;
				shouldFinishTest = 0;				
				out_byte(1);	
			} else { 
				out_byte(0);
			}	
			
			out_byte(accData[0]);
			out_byte(accData[1]);
			out_byte(gyrData[0]);
			out_byte(gyrData[1]);
			out_byte((char)roll);
			out_byte((char)pitch);
			totalSample ++;

		}
/* Test clavier */
		if (kbhit())
			{
				choix = getch();	//lire derniere touche appuyee
				switch (choix)
				{
				case '+':
					if (initialThurst == 0){
						initialThurst = 120;
					} else {
						initialThurst += 5;
					} 
					//if (initialThurst < 200) initialThurst+=5;
					//printf("initialThurst=%d\n",initialThurst);
					break;
				case '-':
					if (initialThurst == 120){
						initialThurst = 0;
					} else {
					initialThurst-=5;
					}
					//printf("initialThurst=%d\n",initialThurst);
					break;
				case 'b':
					if (controlActivated == 1){
						controlActivated = 0;
					} else {
						controlActivated = 1;
					}	
				case 'p':
					out_byte((char)roll);
					out_byte((char)pitch);
				break;	
				case 'o':
					out_byte(accData[0]);
					out_byte(accData[1]);
					out_byte(accData[2]);
					out_byte(gyrData[0]);
					out_byte(gyrData[1]);
					out_byte(gyrData[2]);
				break;
				case 'a':
					MCF_DTIM0_DTMR=0x501B;
					testMode = 1;
				break;


				case (27):
				case (10):		// Arret d'urgence
					stopTest();
					return(0);
					break;
			
				}
			}
	}		
}

void stopTest(){
	initialThurst = 0;
    thrustOffset = 0;
	MCF_PWM_PWMDTY1 = 0;	//couper les PWM
	MCF_PWM_PWMDTY3 = 0;
	MCF_PWM_PWMDTY5 = 0;
	MCF_PWM_PWMDTY7 = 0;


	MCF_DTIM0_DTMR=0x500B;
	nirq = 0;
	testMode = 0;

	//test(2,3);
}

void Init_PWM (void)
{
	MCF_GPIO_DDRTD = MCF_GPIO_DDRTD | 0x0F; 		//config en sortie TD0
	MCF_GPIO_PTDPAR = MCF_GPIO_PTDPAR | 0x0F;		// configure en PWM
	
	MCF_PWM_PWME = MCF_PWM_PWME | 0xAA; 			//active PWMOUT1
	MCF_PWM_PWMPOL = MCF_PWM_PWMPOL | 0xAA; 		//niveau bas au debut puis haut
	MCF_PWM_PWMCLK = MCF_PWM_PWMCLK | 0xAA; 		//selectionne la clock A / B 
	
	MCF_PWM_PWMPRCLK = MCF_PWM_PWMPRCLK | 0x11;		//divise l'horloge A / B par 4
	MCF_PWM_PWMCAE = MCF_PWM_PWMCAE & 0x55; 		//choisi l'alignement
	MCF_PWM_PWMCTL = MCF_PWM_PWMCTL & 0x0F; 		//PWM1 configuré sur 8bits
	MCF_PWM_PWMSDN = MCF_PWM_PWMSDN & 0xBF; 		//desactive les interruptions
	
	MCF_PWM_PWMSCLA = 0x63; 						//redivise la clock A par 52
	MCF_PWM_PWMSCLB = 0x63; 						//redivise la clock B par 52
	
	MCF_PWM_PWMPER1 = 0xFF; 						//periode de 255
	MCF_PWM_PWMPER3 = 0xFF; 						//periode de 255
	MCF_PWM_PWMPER5 = 0xFF; 						//periode de 255
	MCF_PWM_PWMPER7 = 0xFF; 						//periode de 255
}		

void Init_5213(void)
{
//configuration des broches multifonctions
	MCF_GPIO_PUAPAR &= 0x3F;	// Port UCTS0 en GPIO pour le CS du gyro
	MCF_GPIO_PQSPAR = 0x0015;	//QS4 GPIO(CS Acc), QS3..1 en primary pour SPI	

	//Config Timer0 pour temporiser les échelons à 0.2s
	MCF_DTIM0_DTMR=0x500B; //RAZ auto, pas de prediv 16, IT
	MCF_DTIM0_DTRR=19999; //Registre Reference pour 100Hz
	MCF_DTIM0_DTCN=0; //RAZ registre Compteur
	MCF_DTIM0_DTER=0x03; //RAZ registre Drapeaux

	MCF_INTC_ICR19 = MCF_INTC_ICR_IL(0x5);
	MCF_INTC_ICR21 = MCF_INTC_ICR_IL(0x5);
	MCF_INTC_IMRL = MCF_INTC_IMRL & ~(MCF_INTC_IMRL_MASK19 | MCF_INTC_IMRL_MASK21);
	
	io_32(ADR_VECT_INT0) = (long)isrINT0; // Chargement du vecteur d'interruption dans la table
	io_32(ADR_VECT_INT2) = (long)isrINT2;
	__asm("move.w #0x2200,%sr\n");	 // Initialisation a 2 du masque de priorite d'interruption dans le registre d'etat	
	
	//Config Timer2 pour calcul des temps passés, toutes les uS (prediv 80)
	MCF_DTIM2_DTMR=0x500B; //RAZ auto, pas de prediv 16, pas d'IT
	MCF_DTIM2_DTRR=1; //Registre Reference pour 1MHz
	MCF_DTIM2_DTCN=0; //RAZ registre Compteur
	MCF_DTIM2_DTER=0x03; //RAZ registre Drapeaux	

	//Config Timer3 pour echantillonage 100Hz A PARTIR DE CLK+80MHZ
	//division par 80 par prediv puis ref=10000 => 100HZ
	MCF_DTIM3_DTMR=0x500B; //RAZ auto, pas de prediv 16, pas d'IT
	MCF_DTIM3_DTRR=9999; //Registre Reference pour 100Hz
	MCF_DTIM3_DTCN=0; //RAZ registre Compteur
	MCF_DTIM3_DTER=0x03; //RAZ registre Drapeaux	
	
	//Proprietes du transfert SPI
	MCF_QSPI_QMR = 0xA308;		//tfert 8 bits, CPOL=1, CPHA=1 fclk=1Mhz
	MCF_QSPI_QDLYR = 0x0000;   	//Activation du  bus SPI   //////>>   pour init un transfert mettre 0x8000
	MCF_QSPI_QWR = 0x0000;     	//Pointeurs de la RAM (FIFO limitee a un mot)    
	MCF_QSPI_QIR = 0xD00D;     	//Drapeau fin de transfert
	MCF_QSPI_QAR = 0x0020;		//selection RAM de commande
	MCF_QSPI_QDR = 0x0E00;		// A  defaut
	
	// init des CS Gyro et accelero	
	MCF_GPIO_DDRUA|=0x08;		// CS du gyro mis en sortie
	MCF_GPIO_SETUA=0x08;		// mise à niveau haut du CS gyro
	MCF_GPIO_DDRQS|=0x10;		// CS de l'accéléro mis en sortie
	MCF_GPIO_SETQS=0x10;		// mise à niveau haut du CS acc
}	


void GetInertie(void)
{
	char bufAcc[6],bufGyro[6];
	//short gyrData[3], accData[3];

	unsigned char ad, datawrite, dataread;
	unsigned char gyro_value,acc_value;

	double doubleX,doubleY;
//lecture des donnees
	CSA_ON;
	SpiRead6R(bufAcc);
	CSA_OFF;
	CSG_ON;
	SpiRead6R(bufGyro);
	CSG_OFF;


	accData[0] = bufAcc[1];
	accData[1] = bufAcc[3];
	accData[2] = bufAcc[5];

	gyrData[0] = bufGyro[3];
	gyrData[1] = bufGyro[1];
	gyrData[2] = bufGyro[5];	
}

void ComplementaryFilter(char accData[3], char gyrData[3], double *pitch, double *roll)
{
    double pitchAcc, rollAcc;               
 

    // Integrate the gyroscope data -> int(angularSpeed) = angle
    *pitch += (gyrData[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
    *roll -= (gyrData[1] / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis

    int forceMagnitudeApprox = abs(accData[0]) + abs(accData[1]) + abs(accData[2]);
    if (forceMagnitudeApprox > 32 && forceMagnitudeApprox < 128) // 32 - 128 -- 8192 - 32768
    {
	// Turning around the X axis results in a vector on the Y-axis

        pitchAcc = atan2f(accData[1], accData[2]) * 180 / PI; // 0 - 2
        *pitch = *pitch * (1 - compFilterCoef) + pitchAcc * compFilterCoef;
 
	// Turning around the Y axis results in a vector on the X-axis
        rollAcc = atan2f(accData[0], accData[2]) * 180 / PI; // 1 - 2
        *roll = *roll * (1 - compFilterCoef) + rollAcc * compFilterCoef;

    }
} 


