/* Projet : Quadricopter
fichier : 4xCopter.c
Objet : prog principal d'asservissement
autheurs : VG / J-E G-B
Version :	1.0 - 27-06-2013 Tests de base
			1.1 - 11-07-2013 Mise en route des moteurs !
*/

#include "stdio.h"
#include "main.h"
#include "config.h"
#include "libs/spiUtils/spiUtils.h"
#include "libs/mcf5213/mcf5213.h"
#include <math.h>


int rollFromGyro=0, pitchFromGyro=0;
int pitchFromAcc=0, rollFromAcc=0;


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
void ComplementaryFilter(char aData[3], char gData[3], int *pitch, int *roll);
int __atan2(float y, float x);


void GetInertie(void);

int pitch = 0,roll = 0;

int lastPitch, lastRoll, deltaPitch, deltaRoll;
int targetPitch = 0, targetRoll = 0, targetYawSpeed = 0;
int errorPitch = 0, errorRoll = 0, errorYawSpeed = 0;
int integratedErrorPitch = 0, integratedErrorRoll = 0, integratedErrorYawSpeed=0;
int control_roll=0, control_pitch=0, control_yaw=0;

int PTerm, ITerm, DTerm;

char controlMode = 0,controlActivated = 0;

char appState = 'a';

int thrustOn = 0;
int a = 2, b = 3, c = 9;

unsigned char m4offset = 5;

#define dt 0.01
#define freq 100

#define timeConstant 0.5
#define compFilterCoef timeConstant / (timeConstant + dt)//0.9782;

unsigned char kP = 28, kI = 46, kD = 11; // idea: 19 70 5

int shouldTrace = 0;

void actionINT0(void) {
	//unsigned int ii;
	/*nirq++;
	switch(nirq){
		case 1:
			thrustOffset = 0;
			initialThurst = 0;
		break;

		case 120:
			initialThurst = 120;
		break;	

		case 220:
			initialThurst = 120;
		break;	


		case 320:
			initialThurst = 120;
		break;			

		case 440:		
			thrustOffset = 0;
			initialThurst = 0;
			MCF_DTIM0_DTMR=0x500B;
			nirq = 0;
			shouldFinishTest = 1;
		break;
	}	//printf("Occurence num. %d de TIMER1 \n", nirq);

	// Acquittement de l'interruption
	MCF_DTIM0_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;*/
}

void actionINT2(void) {
	//unsigned int ii;
	timeClock += 1;
	// Acquittement de l'interruption
	MCF_DTIM2_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

int main (void)
{	
	controlMode = 0;
	controlActivated = 0;
	testMode = 0;

	printf("Starting ...:\n");
	char temp, choix,_r,_p;
	unsigned int i, throttle,st;
	throttle = 0,st = 0;
	
	
/*Init des IOs*/	
	Init_5213();		//bus SPI
	Init_PWM();
	int result = Init_sensors();
	while(!result){	//Init des composants
		printf("Erreur d'init Acc ou Gyro, retrying ...\n");
		result = Init_sensors();
	}
	printf("Script journées portes ouvertes. Controles:\n");
	printf("Ech: quitter\n");
	printf("o: 12 octets de données de vol\n");
	printf("x: ces mêmes octets mis en formes\n");
	printf("z: mets à zero les angles déterminés selon le gyro\n");
	printf("m1: allume les moteurs à 120\n");
	printf("m0: etteint les moteurs\n");
	getch();
	

	while(1)
	{
		while ((MCF_DTIM3_DTER & 2)==0);//attend prochain date ech
		MCF_DTIM3_DTER = 2;				//RAZ Flag

		GetInertie();	//remplacer par les nouvelles fonctions, voir Sandbox ou MainController
		ComplementaryFilter(accData,gyrData,&pitch,&roll);

	

		errorPitch = targetPitch - pitch/10;
		errorRoll = targetRoll - pitch/10;

		control_pitch = errorPitch / kP;
		control_roll = errorRoll / kP;

		if (appState == 'a'){
			throttle = 0;
			MCF_PWM_PWMDTY7 = throttle;
			MCF_PWM_PWMDTY3 = throttle;

			MCF_PWM_PWMDTY5 = throttle;
			MCF_PWM_PWMDTY1 = throttle;
		} else if (appState == 'b'){
			throttle = 120;
			MCF_PWM_PWMDTY7 = 0;
			MCF_PWM_PWMDTY3 = 0;

			MCF_PWM_PWMDTY5 = throttle;
			MCF_PWM_PWMDTY1 = throttle;

		} else if (appState == 'c'){
			return;
			kP = 15;
			throttle = 20;

			//moteur1 =  throttle + st + control_roll;
			//moteur2 =  throttle + st - control_roll;

			moteur3 =  throttle + control_pitch;
			moteur4 =  throttle - control_pitch + m4offset;

			//MCF_PWM_PWMDTY7 = (unsigned char)sat(moteur1+110,100,135);	
			//MCF_PWM_PWMDTY3 = (unsigned char)sat(moteur2+110,100,135);

			MCF_PWM_PWMDTY5 = (unsigned char)sat(moteur3+110,100,135);
			MCF_PWM_PWMDTY1 = (unsigned char)sat(moteur4+110,100,135);	
		} else if (appState == 'D'){
			return;
			kP = 28;
			throttle = 60;

			errorPitch = targetPitch - pitch/10;

			integratedErrorPitch +=  errorPitch; 
			integratedErrorPitch = sat(integratedErrorPitch,-8000,8000);  		

			deltaPitch = pitch - lastPitch;
			lastPitch = pitch;

			PTerm = errorPitch / kP;
			ITerm = (integratedErrorPitch / freq) / kI;
			DTerm = deltaPitch / kD;

			control_pitch = PTerm + ITerm - DTerm;

			moteur3 =  throttle + st + control_pitch;
			moteur4 =  throttle + st - control_pitch + m4offset;

			MCF_PWM_PWMDTY7 = 0;	
			MCF_PWM_PWMDTY3 = 0;

			MCF_PWM_PWMDTY5 = (unsigned char)sat(moteur3+110,100,190);
			MCF_PWM_PWMDTY1 = (unsigned char)sat(moteur4+110,100,190);	//on limite a 180 pour commencer...
			//
		}

		/*if (thrustOn == 1){
			throttle = 20;

			moteur1 =  throttle + st + control_roll;
			moteur2 =  throttle + st - control_roll;

			moteur3 =  throttle + control_pitch;
			moteur4 =  throttle - control_pitch + m4offset;

			//MCF_PWM_PWMDTY7 = (unsigned char)sat(moteur1+110,100,135);	
			//MCF_PWM_PWMDTY3 = (unsigned char)sat(moteur2+110,100,135);

			MCF_PWM_PWMDTY5 = (unsigned char)sat(moteur3+110,100,135);
			MCF_PWM_PWMDTY1 = (unsigned char)sat(moteur4+110,100,135);	
			printf("Control pitch [%d] \n",control_pitch);		
 
		} else {
			throttle = 0;
			MCF_PWM_PWMDTY7 = throttle;
			MCF_PWM_PWMDTY3 = throttle;

			MCF_PWM_PWMDTY5 = throttle;
			MCF_PWM_PWMDTY1 = throttle;
		}*/

		/* Test clavier */
		if (kbhit())
			{
				choix = getch();	//lire derniere touche appuyee
				switch (choix)
				{	
				case '1':
					targetRoll = (char)getch();
					targetPitch = (char)getch();
				break;			

				case 'z':
					pitchFromGyro = 0;
					rollFromGyro = 0;
				break;
				case '=':
					kP += 1;
					printf("kP [%d] \n",kP);		
				break;
				case '-':
					kP -= 1;
					printf("kP [%d] \n",kP);		
				break;
				case 'a':
					appState = 'a';
				break; 
				case 'b':
					appState = 'b';
				break; 	
				case 'c':
					appState = 'c';
				break;		
				case 'D':
					appState = 'D';
					integratedErrorPitch = 0;
				break;

				case 'o':
					out_byte(accData[0]);
					out_byte(accData[1]);
					out_byte(accData[2]);
					out_byte(gyrData[0]);
					out_byte(gyrData[1]);
					out_byte(gyrData[2]);
					out_byte(pitchFromAcc/100);
					out_byte(pitchFromGyro/100);
					out_byte(pitch/100);
					out_byte(rollFromAcc/100);
					out_byte(rollFromGyro/100);
					out_byte(roll/100);
					out_byte(control_pitch);
					out_byte(control_roll);
				break;									
				case 'x':
					printf("Acc     X:%d  Y:%d  Z:%d \n",(char)accData[0],(char)accData[1],(char)accData[2]);
					printf("Gyro 	X:%d  Y:%d  Z:%d \n",(char)gyrData[0],(char)gyrData[1],(char)gyrData[2]);
					printf("Pitch 	A:%d  G:%d  C:%d \n",pitchFromAcc/100,pitchFromGyro/100,pitch/100);
					printf("Roll 	A:%d  G:%d  C:%d \n",rollFromAcc/100,rollFromGyro/100,roll/100);
				break;

				case 'X':
					printf("Target pitch[%d] roll[%d]",(char)targetPitch,(char)targetRoll);
				break;
			
				case (27):
				case (10):		// Arret d'urgence
					printf("Exit %d\n",choix);	
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
	
	//io_32(ADR_VECT_INT0) = (long)isrINT0; // Chargement du vecteur d'interruption dans la table
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
}	


