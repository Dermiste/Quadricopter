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
#include "libs/sensorUtils/sensorUtils.h"


#define NVECT_TMR0 (64 + 19)
#define NVECT_TMR1 (64 + 20)
#define NVECT_TMR2 (64 + 21)

#define ADR_VECT_INT0 (0x20000000 + NVECT_TMR0*4)
#define ADR_VECT_INT1 (0x20000000 + NVECT_TMR1*4)
#define ADR_VECT_INT2 (0x20000000 + NVECT_TMR2*4)

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

int targetPitch = 0, targetRoll = 0, targetYawSpeed = 0;

int lastPitch = 0, lastRoll = 0, deltaPitch = 0, deltaRoll = 0;

int errorPitch = 0, errorRoll = 0, errorYawSpeed = 0;
int integratedErrorPitch = 0, integratedErrorRoll = 0, integratedErrorYawSpeed=0;

int control_roll=0,control_pitch=0,control_yaw=0;
int PTerm, ITerm, DTerm;
unsigned char m4offset = 3;
//int a=2,b=3,c=4;

char stepPID = 1;

char controlMode = 0,controlActivated = 0;
int a = 2, b = 3, c = 9;

signed int rollFromGyro=0, pitchFromGyro=0;
signed int pitchFromAcc=0, rollFromAcc=0;

unsigned char kP = 42, kI = 70, kD = 13;

int yawFromGyro = 0, intFromAcc = 0;

void actionINT0(void) {
	//MCF_DTIM0_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
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
	nirq++;
	switch(nirq){

		case 5000:		
			MCF_DTIM2_DTMR=0x500B;
			nirq = 0;
			shouldFinishTest = 1;
		break;
	}

	// Acquittement de l'interruption
	MCF_DTIM2_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}


int main (void)
{	
	a = cos(b);
	c = sin(b);
	a = tan(b);
	c = atan(a);
	c = atan2(a,b);
	c = pow(a,b);


	controlMode = 0;
	controlActivated = 0;
	testMode = 0;


	printf("Starting ...:\n");
	char temp, choix,_r,_p;
	unsigned int i, throttle,st;
	throttle = 0,st = 0;
	printf("Reponse indicielle:\n");
	
	Init_5213();		
	Init_PWM();  
	Init_spi();
	int result = Init_sensors();
	while(!result && i){	//Init des composants
		printf("Erreur d'init Acc ou Gyro, retrying ...\n");
		result = Init_sensors();
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

		errorPitch = targetPitch - pitch/10;
		errorRoll = targetRoll - roll/10;	

		//errorYawSpeed = targetYawSpeed - gyrData[2] * 3.906;

		integratedErrorPitch +=  errorPitch; 
		integratedErrorRoll  += errorRoll;
		//integratedErrorYawSpeed += errorYawSpeed;

		integratedErrorPitch = sat(integratedErrorPitch,-7000,7000);  
		integratedErrorRoll =  sat(integratedErrorRoll,-8000,8000);

		deltaRoll = roll - lastRoll;
		lastRoll = roll;	

		deltaPitch = pitch - lastPitch;
		lastPitch = pitch;

		PTerm = errorPitch / kP;
		//PTerm = sat(PTerm,-10,10); 

		ITerm = (integratedErrorPitch / freq) / kI;
		DTerm = deltaPitch / kD;

		control_pitch = PTerm;// + ITerm - DTerm;
		control_pitch += ITerm;
		control_pitch -= DTerm;

		control_roll = errorRoll / kP ;
		control_roll = (integratedErrorRoll / freq ) /  kI;
		control_roll -= deltaRoll / kD;

		//control_yaw = integratedErrorYawSpeed / freq / kI;	
		control_yaw = 0;		

		if (controlActivated){
			if (controlMode){
				//moteur1 =  throttle + st + control_roll;
				//moteur2 =  throttle + st - control_roll;

				moteur3 =  throttle + st + control_pitch;
				moteur4 =  throttle + st - control_pitch + m4offset;

				//MCF_PWM_PWMDTY7 = (unsigned char)sat(moteur1+110,100,210);	
				//MCF_PWM_PWMDTY3 = (unsigned char)sat(moteur2+110,100,210);

				MCF_PWM_PWMDTY5 = (unsigned char)sat(moteur3+110,100,190);
				MCF_PWM_PWMDTY1 = (unsigned char)sat(moteur4+110,100,190);	//on limite a 180 pour commencer...
				//
				throttle = 50;
				//printf("Pitch [%d, %d, %d, %d] \n",pitch/10,control_pitch,integratedErrorPitch,deltaPitch);
				//printf("Roll  [%d, %d, %d] \n",roll/10,errorRoll/10,inategratedErrorRoll/10);
				//printf("Yaw [%d] \n",errorYawSpeed);
				
			} else {
				//initialThurst = 120;
				MCF_PWM_PWMDTY7 = 0;
				MCF_PWM_PWMDTY3 = 0;

				MCF_PWM_PWMDTY5 = initialThurst;// - m4offset;
				MCF_PWM_PWMDTY1 = initialThurst + m4offset;
				throttle = 0;
			}
		} else {
			MCF_PWM_PWMDTY1 = 0;
			MCF_PWM_PWMDTY3 = 0;
			MCF_PWM_PWMDTY5 = 0;
			MCF_PWM_PWMDTY7 = 0;
		}
		 //PTC1=1;


		//MCF_DTIM0_DTER=0x03;
		//printf("Pulse ...\n");

		/*while((MCF_DTIM1_DTER & 0x01 )==0); // Capture 2
		MCF_DTIM1_DTER=0x03; //RAZ registre Drapeau
		imageCap2=MCF_DTIM1_DTCR; //capture 2

		printf("Capture 1 ...\n");

		while((MCF_DTIM1_DTER & 0x01 )==0); // Capture 2
		MCF_DTIM1_DTER=0x03; //RAZ registre Drapeau
		imageCap2=MCF_DTIM1_DTCR; //capture 2		

		printf("Capture 2 ...\n");*/


		 //PTC1=0;		
		//MCF_DTIM0_DTCN=0; //RAZ registre Compteur
		//MCF_DTIM0_DTER=0x03; //RAZ registre Drapeau







		if (testMode){
			if (shouldFinishTest){
				testMode = 0;
				shouldFinishTest = 0;				
				out_byte(1);	
			} else { 
				out_byte(0);
			}	


			/*out_byte(accData[2]);
			out_byte(gyrData[0]);
			out_byte(gyrData[1]);
			out_byte(gyrData[2]);*/
			//out_byte(pitchFromAcc/100);
			//out_byte(pitchFromGyro/100);
			//out_byte((char)(atan2(magData[0],magData[1]) * 180/3.1415));
			//out_byte(__atan2(magData[0],magData[1])/15);
			//out_byte(yaw/150);
			out_byte(magData[0]);
			out_byte(magData[1]);			
			//out_byte(control_pitch);
			//out_byte(control_roll);
		}
		/* Test clavier */
		if (kbhit()) {
			choix = getch();	//lire derniere touche appuyee
			switch (choix)
			{
			case 'z':
				SpiListSlaves();
			break;

			case '1':
				targetRoll = ((char)getch()) * 10;
				targetPitch = ((char)getch()) * 10;
			break;	

			case '=': // + sans le shift
				if (controlActivated)
			    initialThurst += 5;
				printf("Thrust %d\n",initialThurst);
			break;
			case '-':
				if (controlActivated)
				initialThurst -= 5;
				printf("Thrust %d\n",initialThurst);
			break;
			case 'b':
				if (controlActivated == 0){
					controlActivated = 1;
					initialThurst = 120;
				} else { 	
					if (controlMode == 1){
						controlMode = 0;
						initialThurst = 120;
					} else {
						controlMode = 1;
						integratedErrorPitch = 0;
						integratedErrorPitch = 0;
					}
				}	
			break;	
			case 'M':
				if (m4offset != 0){
					m4offset -- ;
					printf("m4offset %d\n",m4offset);
				}
			break;
			case 'm':
				m4offset += 1;
				printf("m4offset %d\n",m4offset);	
			break;	
			case 'p':
				kP += stepPID;
				printf("kP %d kI %d kD %d \n",kP,kI,kD);
			break;
			case 'i':
				kI += stepPID;
				printf("kP %d kI %d kD %d \n",kP,kI,kD);
			break;
			case 'd':
				kD += stepPID;
				printf("kP %d kI %d kD %d \n",kP,kI,kD);
			break;

			case 'P':
				kP -= stepPID;
				printf("kP %d kI %d kD %d \n",kP,kI,kD);
			break;
			case 'I':
				kI -= stepPID;
				printf("kP %d kI %d kD %d \n",kP,kI,kD);
			break;
			case 'D':
				kD -= stepPID;
				printf("kP %d kI %d kD %d \n",kP,kI,kD);
			break;			
			case 'e':
				printf("Pitch: %d Error Pitch: %d \n",pitch/10,errorPitch);
				printf("Roll: %d  Error Roll: %d \n",roll/10,errorRoll);
				printf("Compass: %d  %d  %d\n",magData[0],magData[1],magData[2]);	
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
				printf("Acc X:%d Y:%d Z:%d \n",accData[0],accData[1],accData[2]);
				printf("V 	X:%d Y:%d Z:%d \n",gyrData[0],gyrData[1],gyrData[2]);
				printf("Compass: X:%d  Y:%d  Z:%d\n\n",magData[0],magData[1],magData[2]);
				printf("Pitch : %d Roll : %d Yaw : %d\n",pitch/100, roll/100, yaw/100);	
				getAltitudeAndPressure(&altitudeBaro,&pressure);
				printf("Altitude: Sonar: %dcm Baro: %ddm Pression:%dpa \n\n",altitudeSonar, altitudeBaro, pressure);	

			break;
			case 'a':
				MCF_DTIM2_DTMR=0x501B;
				testMode = 1;


				rollFromGyro = 0;
				pitchFromGyro = 0;

				pitchFromAcc = 0;
				rollFromAcc = 0;

				integratedErrorPitch = 0;
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


