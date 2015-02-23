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

#define PI 3.141592654


#define NVECT_TMR0 (64 + 19)
#define NVECT_TMR2 (64 + 21)
#define ADR_VECT_INT0 (0x20000000 + NVECT_TMR0*4)
#define ADR_VECT_INT2 (0x20000000 + NVECT_TMR2*4)

extern void isrINT0(void);
extern void isrINT2(void);

int _atan2(float y, float x);

int __errno=0;	//pour gestion messages d'erreur des fcts asin, acos de libm.a


unsigned long timeClock,startTime = 0,count;
int sat(int value, int min, int max);
void GetInertie();
void Init_5213(void);
void Init_PWM (void);

char accData[3],gyrData[3];



int totalSample,nirq,testMode,shouldFinishTest = 0;
char tabInertie[] = {0x01,0x0A,0x0C,0x02,0x03,0x0B,0x0C,0x0A,0x22};

void actionINT0(void) {
	//unsigned int ii;
	
	nirq++;
	if (nirq ==  600){
		MCF_DTIM0_DTMR=0x500B;
		nirq = 0;
		shouldFinishTest = 1;
	}
	// Acquittement de l'interruption
	MCF_DTIM0_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

void actionINT2(void) {
	//unsigned int ii;
	timeClock += 1;
	// Acquittement de l'interruption
	MCF_DTIM2_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

void printOutData(){
	out_byte(tabInertie[0]);
	out_byte(tabInertie[1]);
	out_byte(tabInertie[2]);
	out_byte(tabInertie[3]);
	out_byte(tabInertie[4]);
	out_byte(tabInertie[5]);
	out_byte(tabInertie[6]);
	out_byte(tabInertie[7]);
	out_byte(tabInertie[8]);	
}

void printOutData2(){
	//printf("Acc X:%d Y:%d Z:%d \n",accData[0],accData[1],accData[2]);
	//printf("V 	X:%d Y:%d Z:%d \n\n",gyrData[0],gyrData[1],gyrData[2]);}
	printf("atan2f %d \n",(char)(atan2f(1.73,1)* 180 / PI));
	printf("_atan2 %d \n",_atan2(1.73,1));

	printf("atan2f %d \n",(char)(atan2f(-1.73,1)* 180 / PI));
	printf("_atan2 %d \n",_atan2(-1.73,1));

	printf("atan2f %d \n",(char)(atan2f(0.5,1.73/2)* 180 / PI));
	printf("_atan2 %d \n",_atan2(0.5,1.73/2));

	printf("atan2f %d \n",(char)(atan2f(-0.5,1.73/2)* 180 / PI));
	printf("_atan2 %d \n",_atan2(-0.5,1.73/2));		

	printf("Done");

}
int main (void)
{	
	printf("Starting ...:\n");
	char temp, choix;
	unsigned int i, gas, cpt_ech, cpt_moyAngle;
	gas = 0;
	printf("Réponse indicielle:\n");

	
/*Init des IOs*/	
	Init_5213();		//bus SPI
	getch();

	int result = Init_AccGyro();
	while(!result){	//Init des composants
		printf("Erreur d'init Acc ou Gyro, retrying ...\n");
		result = Init_AccGyro();
	}	
	

	while(1)
	{
		//if ((MCF_DTIM3_DTER & 2)!=0)	//en retard sur echantillonnage ?
			//printf("Ech rate!!\n");	
		//Test(2,3);
		while ((MCF_DTIM3_DTER & 2)==0);
			//printf("wait");

		MCF_DTIM3_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
			
		GetInertie();
		//attend prochain date ech
						//RAZ Flag	
	
		count ++;

		//if (!(count % 100)){
			//printf("Time is %d",count/100);
		//}

		if (testMode){
			if (shouldFinishTest){
				out_byte(1);	
				testMode = 0;
				shouldFinishTest = 0;
			} else { 
				out_byte(0);
			}	

			out_byte(tabInertie[0]);
			out_byte(tabInertie[1]);
			out_byte(tabInertie[2]);
			out_byte(tabInertie[3]);
			out_byte(tabInertie[4]);
			out_byte(tabInertie[5]);
			out_byte(tabInertie[6]);
			out_byte(tabInertie[7]);
			out_byte(tabInertie[8]);
			out_byte(tabInertie[8]);
			totalSample ++;

			if (testMode == 0){
				//printf("Total sample : %d",totalSample);
			}
		}
/* Test clavier */
		if (kbhit())
			{
				choix = getch();	//lire derniere touche appuyee
				switch (choix)
				{
				case 'a':
					MCF_DTIM0_DTMR=0x501B;
					testMode = 1;
					break;

				case 'o':
					//startTime = timeClock;
					printOutData2();
					//printf("\nTime for 9 bytes: %d \n",timeClock - startTime);
					break;					

				case (27):
				case (10):		// Arret d'urgence
					nirq = 0;
					testMode = 0;
					return(0);
					break;
			
				}
			}
	}		
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
	
	//Config Timer2 pour calcul des temps passés, toutes les uS
	//division par 80 par prediv puis ref=10000 => 100HZ
	MCF_DTIM2_DTMR=0x501B; //RAZ auto, pas de prediv 16, pas d'IT
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

	//printf("1 Acc X:%d Y:%d Z:%d \n",bufAcc[1],bufAcc[3],bufAcc[5]);

	accData[0] = bufAcc[1];
	accData[1] = bufAcc[3];
	accData[2] = bufAcc[5];

	//printf("2 Acc X:%d Y:%d Z:%d \n\n",accData[0],accData[1],accData[2]);


	gyrData[0] = bufGyro[1];
	gyrData[1] = bufGyro[3];
	gyrData[2] = bufGyro[5];	
}

int _atan2(float y, float x){
  //#define fp_is_neg(val) ((((unsigned char*)&val)[3] & 0x80) != 0)
  float z = y / x;
  int zi = abs((int)(z * 100)); 
  //unsigned char y_neg = fp_is_neg(y);
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
