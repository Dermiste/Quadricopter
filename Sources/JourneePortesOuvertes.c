/* Projet : Quadricopter
fichier : 4xCopter.c
Objet : prog principal d'asservissement
autheurs : VG / J-E G-B
Version :	1.0 - 27-06-2013 Tests de base
			1.1 - 11-07-2013 Mise en route des moteurs !
*/

#include "stdio.h"
#include "main.h"
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
signed int control_roll=0,control_pitch=0,control_yaw=0;


char controlMode = 0,controlActivated = 0;

int thrustOn = 0;

#define dt 0.01
#define freq 100

#define timeConstant 0.5
#define compFilterCoef timeConstant / (timeConstant + dt)//0.9782;

char kP = 50, kI = 75, kD = 20;

int shouldTrace = 0;

void actionINT0(void) {
	//unsigned int ii;
	nirq++;
	switch(nirq){
		case 1:
			thrustOffset = 0;
			initialThurst = 0;
		break;

		/*case 120:
			initialThurst = 120;
		break;	*/	

		case 220:
			initialThurst = 140;
		break;	

/*
		case 320:
			initialThurst = 140;
		break;	*/			

		case 440:		
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
	controlMode = 0;
	controlActivated = 0;
	testMode = 0;

	printf("Starting ...:\n");
	char temp, choix,_r,_p;
	unsigned int i, throttle,st;
	throttle = 0,st = 0;
	printf("Reponse indicielle:\n");
	
/*Init des IOs*/	
	Init_5213();		//bus SPI
	Init_PWM();
	int result = Init_AccGyro();
	while(!result){	//Init des composants
		printf("Erreur d'init Acc ou Gyro, retrying ...\n");
		result = Init_AccGyro();
	}

	//printf("Status=%d\n",temp );		
	//printf("taper touche\n");
	getch();
	

	while(1)
	{
		while ((MCF_DTIM3_DTER & 2)==0);//attend prochain date ech
		MCF_DTIM3_DTER = 2;				//RAZ Flag

		GetInertie();	//retourne dans tabInertie les valeurs
		//printf("Gyr X:%d Y:%d Z:%d \n",gyrData[0],gyrData[1],gyrData[2]);
		ComplementaryFilter(accData,gyrData,&pitch,&roll);
		//printf("After Filter Gyr X:%d Y:%d Z:%d \n",gyrData[0],gyrData[1],gyrData[2]);	

		/*if (controlActivated){
			if (controlMode){
				errorPitch = targetPitch - pitch/10;
				errorRoll = targetRoll - roll/10;	
				errorYawSpeed = targetYawSpeed - gyrData[2] * 3.906;


				//printf("Integrated error pitch : %d \n",(signed int)integratedErrorPitch);
				integratedErrorPitch +=  errorPitch; 
				integratedErrorRoll  += errorRoll;
				integratedErrorYawSpeed += errorYawSpeed;

				integratedErrorPitch = sat(integratedErrorPitch,-10000,10000);  // + ou - 300 
				integratedErrorRoll =  sat(integratedErrorRoll,-10000,10000);

				deltaPitch = pitch - lastPitch;
				lastPitch = pitch;

				deltaRoll = roll - lastRoll;
				lastRoll = roll;				

				control_pitch = errorPitch / kP + (integratedErrorPitch / freq) / kI - deltaPitch / kD;
				control_roll = errorRoll / kP  + (integratedErrorRoll / freq ) /  kI - deltaRoll / kD;

				control_yaw = integratedErrorYawSpeed / freq / kI;	
				control_yaw = 0;	

				moteur1 =  throttle + st + control_roll;
				moteur2 =  throttle + st - control_roll - control_yaw;

				moteur3 =  throttle + st + control_pitch + control_yaw;
				moteur4 =  throttle + st - control_pitch;

				MCF_PWM_PWMDTY7 = (unsigned char)sat(moteur1+110,100,180);	
				MCF_PWM_PWMDTY3 = (unsigned char)sat(moteur2+110,100,180);

				//MCF_PWM_PWMDTY5 = (unsigned char)sat(moteur3+110,100,180);
				//MCF_PWM_PWMDTY1 = (unsigned char)sat(moteur4+110,100,180);	//on limite a 180 pour commencer...
				
				throttle = 25;
				//printf("Pitch [%d, %d, %d, %d] \n",pitch/100,control_pitch,integratedErrorPitch/10,deltaPitch);
				//printf("Roll  [%d, %d, %d] \n",roll/10,errorRoll/10,integratedErrorRoll/10);
				printf("Yaw [%d] \n",errorYawSpeed);
			} else {
				MCF_PWM_PWMDTY7 = 120;
				MCF_PWM_PWMDTY3 = 120;

				MCF_PWM_PWMDTY5 = 120;
				MCF_PWM_PWMDTY1 = 120;
				throttle = 0;
			}
		} else {
			MCF_PWM_PWMDTY1 = initialThurst;
			//MCF_PWM_PWMDTY3 = initialThurst;
			MCF_PWM_PWMDTY5 = initialThurst;
			//MCF_PWM_PWMDTY7 = initialThurst;
		}*/
			if (shouldTrace){
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
			}

			if (thrustOn == 1){
				MCF_PWM_PWMDTY7 = 120;
				MCF_PWM_PWMDTY3 = 120;

				//MCF_PWM_PWMDTY5 = 120;
				//MCF_PWM_PWMDTY1 = 120;
			} else {
				MCF_PWM_PWMDTY7 = 0;
				MCF_PWM_PWMDTY3 = 0;

				MCF_PWM_PWMDTY5 = 0;
				MCF_PWM_PWMDTY1 = 0;
			}
		/* Test clavier */
		if (kbhit())
			{
				choix = getch();	//lire derniere touche appuyee
				switch (choix)
				{
				/*case '=': // + sans le shift
				    st += 2;
					break;
				case '-':
					if (st != 0)
						st -= 2;
					break;
				case 'b':
					if (controlActivated == 0){
						controlActivated = 1;
					} else { 	
						if (controlMode == 1){
							controlMode = 0;
						} else {
							controlMode = 1;
						}	
					}		*/	
				case 'z':
					pitchFromGyro = 0;
					rollFromGyro = 0;
				break;
				case 'm':
					if (getch() == '1'){
						thrustOn = 1;
					} else {
						thrustOn = 0;
					}
				break;

				case 't':
					if (shouldTrace == 0)
					shouldTrace = 1;
					else
					shouldTrace = 0;
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
				break;									
				case 'x':
					printf("Acc X:%d Y:%d Z:%d \n",(char)accData[0],(char)accData[1],(char)accData[2]);
					printf("Gyro 	X:%d Y:%d Z:%d \n",(char)gyrData[0],(char)gyrData[1],(char)gyrData[2]);
					printf("Pitch 	A:%d G:%d C:%d \n",pitchFromAcc/100,pitchFromGyro/100,pitch/100);
					printf("Roll 	A:%d G:%d C:%d \n",rollFromAcc/100,rollFromGyro/100,roll/100);
				break;
				/*case 'a':
					MCF_DTIM0_DTMR=0x501B;
					testMode = 1;

					rollFromGyro = 0;
					pitchFromGyro = 0;

					pitchFromAcc = 0;
					rollFromAcc = 0;
				break;*/
			
				case (27):
				case (10):		// Arret d'urgence
					//printf("Exit %d\n",choix);	
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

	gyrData[0] = bufGyro[1];
	gyrData[1] = bufGyro[3];
	gyrData[2] = bufGyro[5];	
}

void ComplementaryFilter(char aData[3], char gData[3], int *pitch, int *roll)
{
    int pitchAcc, rollAcc;               
 	

    *pitch += 100 * gData[0] * 3.906 * dt; // Angle around the X-axis
    *roll -= 100 * gData[1] * 3.906 * dt;    // Angle around the Y-axis

    //if (testMode){
    pitchFromGyro += 100 * (gData[0] * 3.906) * dt;
    rollFromGyro -= 100 * (gData[1] * 3.906) * dt; 
	//}

    int forceMagnitudeApprox = abs(aData[0]) + abs(aData[1]) + abs(aData[2]);
    if (forceMagnitudeApprox > 32 && forceMagnitudeApprox < 128) // 32 - 128 -- 8192 - 32768
    {
    	//if (testMode){
    	pitchFromAcc = 10 * __atan2(aData[0], aData[2]);
    	rollFromAcc = 10 * __atan2(-aData[1], aData[2]);
    	//}

        pitchAcc = 10 * __atan2(aData[0], aData[2]); // 1 2
        *pitch = *pitch * compFilterCoef + pitchAcc * (1 - compFilterCoef);


        rollAcc = 10 * __atan2(-aData[1], aData[2]); //-0 2
        *roll = *roll * compFilterCoef + rollAcc * (1 - compFilterCoef);
    }
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


