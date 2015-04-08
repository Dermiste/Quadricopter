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


#define NVECT_TMR0 (64 + 19)
#define NVECT_TMR1 (64 + 20)
#define NVECT_TMR2 (64 + 21)

#define ADR_VECT_INT0 (0x20000000 + NVECT_TMR0*4)
#define ADR_VECT_INT1 (0x20000000 + NVECT_TMR1*4)
#define ADR_VECT_INT2 (0x20000000 + NVECT_TMR2*4)

#define test 4;
#define tes 2;

extern void isrINT0(void);
extern void isrSonar(void);
extern void isrTempo1ms(void);

void Init_5213(void);
void Init_PWM (void);
void receiveAndSendCommands();

int imageCap1 = 0, imageCap2 = 0, imagetemps;

char gyrData[3];
char accData[3];
char magData[3];
char buf[6];


int __errno=0;	//pour gestion messages d'erreur des fcts asin, acos de libm.a
int nirq = 0;
signed int moteur1,moteur2,moteur3,moteur4;

unsigned int initialThurst = 0;
int thrustOffset = 0;
int totalSample = 0;
unsigned int testMode = 0,shouldFinishTest = 0;

int altitudeSonar = 0, altitudeBaro = 0, pressure = 0;
int pitch = 0,roll = 0, yaw = 0;


int a = 2, b = 3, c = 9;

unsigned char kP = 42, kI = 70, kD = 13;

void actionINT0(void) {
	
	MCF_DTIM0_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

void actionSonar(void) {
	if (imageCap1 == 0){
		imageCap1 = MCF_DTIM1_DTCR;
	} else {
		imageCap2 = MCF_DTIM1_DTCR;
		imagetemps=imageCap2-imageCap1;  //image impulsion = capture 2 -capture 1

		altitudeSonar=(imagetemps*100)/7000;

        imageCap1 = 0;	       
	}

	MCF_DTIM1_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

void actionTempo1ms(void) {
	printf("actionTempo1ms \n");

	MCF_DTIM2_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}


int main (void)
{	
	a = cos(b);
	c = sin(b);
	a = tan(b);
	c = atan(a);
	c = pow(a,b);

	printf("Starting ...:\n");
	char temp, choix,_r,_p;
	unsigned int i = 3;
	printf("Reponse indicielle:\n");
	
	Init_5213();		
	Init_PWM();  
	Init_spi();
	int result = Init_sensors();
	while(!result && i){	//Init des composants
		printf("Erreur d'init Acc ou Gyro, retrying ...\n");
		result = Init_sensors();
		i --;
	}



	getch();

	while(1)
	{
		while ((MCF_DTIM3_DTER & 2)==0);//attend prochain date ech
		MCF_DTIM3_DTER = 2;				//RAZ Flag


		MCF_GPIO_CLRTC=0x00;
		for(i=0;i<2000;i++); //Temporisation
		MCF_GPIO_SETTC=0x01;

		getIMUdata(accData, gyrData, magData);
		filterIMUdata(accData, gyrData, magData, &pitch, &roll, &yaw);

		/* Test clavier */
		if (kbhit()) {
			choix = getch();	//lire derniere touche appuyee
			switch (choix)
			{
			case 'z':
				SpiListSlaves();
			break;

			case 'x':
				printf("Acc X:%d Y:%d Z:%d \n",accData[0],accData[1],accData[2]);
				printf("V 	X:%d Y:%d Z:%d \n",gyrData[0],gyrData[1],gyrData[2]);
				printf("Compass: X:%d  Y:%d  Z:%d\n\n",magData[0],magData[1],magData[2]);
				printf("Pitch : %d Roll : %d Yaw : %d\n",pitch/100, roll/100, yaw/10);	
				getAltitudeAndPressure(&altitudeBaro,&pressure);
				printf("Altitude: Sonar: %dcm Baro: %ddm Pression:%dpa \n\n",altitudeSonar, altitudeBaro, pressure);	
			break;
		

			case (27):
			case (10):		// Arret d'urgence
				printf("Exit %d\n",choix);	
				printf("kP %d kI %d kD %d \n",kP,kI,kD);
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
	MCF_GPIO_PTCPAR = MCF_GPIO_PTCPAR & ~(MCF_GPIO_DDRTC_DDRTC0 | MCF_GPIO_DDRTC_DDRTC1); // OK // PAR, 0 for GPIO, 1 for primary function
	MCF_GPIO_PTCPAR = MCF_GPIO_PTCPAR | MCF_GPIO_DDRTC_DDRTC2;
	//printf("MCF_GPIO_PTCPAR 0x%x \n\n",MCF_GPIO_PTCPAR);

	MCF_GPIO_DDRTC = MCF_GPIO_DDRTC | MCF_GPIO_DDRTC_DDRTC0; // OK // DDR, set for output, clear for input
	MCF_GPIO_DDRTC = MCF_GPIO_DDRTC & ~MCF_GPIO_DDRTC_DDRTC1;
	//printf("MCF_GPIO_DDRTC 0x%x \n",MCF_GPIO_DDRTC);

	MCF_GPIO_PQSPAR = 0x0015;	//QS4 GPIO(CS Acc), QS3..1 en primary pour SPI	

	//Config Timer1 pour capture de l'écho du sonar
	MCF_DTIM1_DTMR=0x40C3; 
	MCF_DTIM1_DTRR=0xFFFFFFFF; 
	MCF_DTIM1_DTCN=0; //RAZ registre Compteur
	MCF_DTIM1_DTER=0x03; //RAZ registre Drapeaux

	MCF_INTC_ICR20 = MCF_INTC_ICR_IL(0x5); // Timer 1
	MCF_INTC_ICR21 = MCF_INTC_ICR_IL(0x5); // Timer 2
	MCF_INTC_IMRL = MCF_INTC_IMRL & ~(MCF_INTC_IMRL_MASK20 | MCF_INTC_IMRL_MASK21);
	
	io_32(ADR_VECT_INT1) = (long)isrSonar; // Chargement du vecteur d'interruption dans la table
	io_32(ADR_VECT_INT2) = (long)isrTempo1ms;
	__asm("move.w #0x2200,%sr\n");	 // Initialisation a 2 du masque de priorite d'interruption dans le registre d'etat	
	
	//Config Timer2 pour temporiser suites de commandes + impulsion sonar
	MCF_DTIM2_DTMR=0x500B; //RAZ auto, pas de prediv 16, pas d'IT 
	MCF_DTIM2_DTRR=1000; //Registre Reference pour 1MHz
	MCF_DTIM2_DTCN=0; //RAZ registre Compteur
	MCF_DTIM2_DTER=0x03; //RAZ registre Drapeaux	

	//Config Timer3 pour echantillonage 100Hz A PARTIR DE CLK+80MHZ
	//division par 80 par prediv puis ref=10000 => 100HZ
	MCF_DTIM3_DTMR=0x500B; //RAZ auto, pas de prediv 16, pas d'IT
	MCF_DTIM3_DTRR=9999; //Registre Reference pour 100Hz
	MCF_DTIM3_DTCN=0; //RAZ registre Compteur
	MCF_DTIM3_DTER=0x03; //RAZ registre Drapeaux	
}	


