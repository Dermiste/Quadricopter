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



#define PI 3.141592654

// moteur1 PWMDTY7
// moteur2 PWMDTY3
// moteur3 PWMDTY5
// moteur4 PWMDTY1

#define NVECT_TMR0 (64 + 19)
#define ADR_VECT_INT0 (0x20000000 + NVECT_TMR0*4)

extern void isrINT0(void);

//Variables globales
char tabInertie[9];
	//contenu tabInertie : ThetaX, ThetaY, AccZ, dThetaX,dThetaY,dThetaZ,D²ThetaX,d²ThetaY,d²ThetaZ
char bufGyroOld[6];	//pour calcul derivee vitesse angulaire (acceleration angulaire)
char tabMoyAX[64];	//moyenner mesure d'assiette
char tabMoyAY[64];
char *pTabmoyAX,*pTabmoyAY;


int __errno=0;	//pour gestion messages d'erreur des fcts asin, acos de libm.a
int control_r=0,control_p=0,control_y=0;
int GvX,GvY,GvZ,GaX,GaY,IGpX,IGpY;	//gains asservissement
int SumAY=0,SumAX=0;	//moyennage Angles
char MoyAX,MoyAY;	//Angles moyennes
int nirq = 0;
int moteur1,moteur2,moteur3,moteur4;
unsigned char PWMot1,PWMot2,PWMot3,PWMot4;

int sat(int value, int min, int max);
void Init_5213(void);
void Init_PWM (void);

void actionINT0(void) {
	//unsigned int ii;
	
	nirq++;
	printf("Occurence num. %d de TIMER1 \n", nirq);

	// Acquittement de l'interruption
	MCF_DTIM0_DTER = MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP;
}

/*int main(void){
	printf("Starting ...:\n");

	char choix = 0;

	MCF_DTIM0_DTMR=0x501B; //RAZ auto, pas de prediv 16, IT
	MCF_DTIM0_DTRR=19999; //Registre Reference pour 100Hz
	MCF_DTIM0_DTCN=0; //RAZ registre Compteur
	MCF_DTIM0_DTER=0x03; //RAZ registre Drapeaux

	//MCF_INTC_ICR19 = 0x28;
	MCF_INTC_ICR19 = MCF_INTC_ICR_IL(0x5);
	
	MCF_INTC_IMRL = MCF_INTC_IMRL & ~(MCF_INTC_IMRL_MASK19);
	//MCF_INTC_IMRL = 0xfff7ffff;
	io_32(ADR_VECT_INT0) = (long)isrINT0; // Chargement du vecteur d'interruption dans la table
	__asm("move.w #0x2500,%sr\n");	 // Initialisation a 2 du masque de priorite d'interruption dans le registre d'etat	
	
	while(1){
		if (kbhit())
		{
			choix = getch();	//lire derniere touche appuyee
			switch (choix)
			{
			case 'a':
				__asm("move.w #0x2200,%sr\n");
				break;
			case 'b':
				__asm("move.w #0x2500,%sr\n");
				break;				
			case (27):
				printf("Quitting with %d ...:\n",choix);
				return(0);
				break;
			default:
				break;
			}
		}
	}

}*/

int main (void)
{	
	printf("Starting ...:\n");
	char temp, choix;
	unsigned int i, gas, cpt_ech, cpt_moyAngle, initialThurst;
	gas = 0;
	initialThurst = 0;
	printf("Réponse indicielle:\n");


	/*printf("+ ou - pour les gas\n");
	printf("V / v pour gain Gv X et Y\n");
	printf("A / a pour gain Ga X et Y\n");
	printf("Z / z pour gain GvZ\n");*/
	
	
/* INIT des gains*/
	GaX=1;
	GaY=1;
	GvX=2;
	GvY=2;
	GvZ=1;
	IGpX=4;	//gain 1/4
	IGpY=4;
	
/*Init des pointeurs de moyennage et des tableaux*/
	for(pTabmoyAX=tabMoyAX;pTabmoyAX<=tabMoyAX+sizeof(tabMoyAX)-1;pTabmoyAX++)
		*pTabmoyAX=0;
	for(pTabmoyAY=tabMoyAY;pTabmoyAY<=tabMoyAY+sizeof(tabMoyAY)-1;pTabmoyAY++)
		*pTabmoyAY=0;
	pTabmoyAX=tabMoyAX;
	pTabmoyAY=tabMoyAY;
	
/*Init des IOs*/	
	Init_5213();		//bus SPI
	Init_PWM();
	if(Init_AccGyro())	//Init des composants
		printf("Erreur d'init Acc ou Gyro\n");
	//RAZ de tabInertieOld pour premier calcul de derivee
	for(i=0;i<6;i++)
		bufGyroOld[i]=0;
		
//lecture temp sur Gyro :	
	CSG_ON;
	temp=SpiRead8(ST_GYRO_OUT_TEMP);
	CSG_OFF;
	//printf("TempGyro=%d\n",temp );
	//printf("taper touche\n");
	getch();
	

	while(1)
	{
		if ((MCF_DTIM3_DTER & 2)!=0)	//en retard sur echantillonnage ?
			printf("Ech rate!!\n");	
		while ((MCF_DTIM3_DTER & 2)==0);//attend prochain date ech
		MCF_DTIM3_DTER = 2;				//RAZ Flag

		GetInertie();	//retourne dans tabInertie les valeurs
		
		//fenêtre de moyennage sur 8 echantillons pour l'assiette
		SumAX-=*pTabmoyAX;	//retrancher l'element le + ancien de la somme de la moyenne glissante
		*pTabmoyAX=AX;		//insérer dans le tableau circulaire le nouvel element
		SumAX+=*pTabmoyAX;	//mettre a jour la somme
		if (pTabmoyAX==(tabMoyAX+sizeof(tabMoyAX)-1))	//fin de buffer circulaire atteinte ?
			pTabmoyAX=tabMoyAX;			//repointer au début
		else
			pTabmoyAX++;	//déplacer le pointeur de buffer circulaire

		MoyAX=SumAX/sizeof(tabMoyAX);		//diviser pour calculer la moyenne
		
		SumAY-=*pTabmoyAY;	//retrancher l'element le + ancien de la somme de la moyenne glissante
		*pTabmoyAY=AY;		//insérer dans le tableau circulaire le nouvel element
		SumAY+=*pTabmoyAY;	//mettre a jour la somme
		if (pTabmoyAY==(tabMoyAY+sizeof(tabMoyAY)-1))	//fin de buffer circulaire atteinte ?
			pTabmoyAY=tabMoyAY;			//repointer au début
		else
			pTabmoyAY++;	//déplacer le pointeur de buffer circulaire
		
		MoyAY=SumAY/sizeof(tabMoyAY);		//diviser pour calculer la moyenne
		
		/*		
		 cpt_moyAngle++;		//compteur de moyennage
		 SumAY+=AY;			// Il faudrait faire en fait une moyenne glissante
		 SumAX+=AX;
		 if (cpt_moyAngle>15) {
		 cpt_moyAngle=0;
		 MoyAX=(char)SumAX>>4;
		 MoyAY=(char)SumAY>>4;
		 SumAX=0; SumAY=0;
		 }
		 */
		//control_r=sat(GvX*VAX,-100,100) + sat(GaX*AAX,-50,50) + MoyAX/IGpX; //axe X
		//control_p=-sat(GvY*VAY,-100,100) + sat(GaY*AAY,-50,50) - MoyAY/IGpY ;//axe Y
		//control_y=sat(GvZ*VAZ,-50,50);//+sat(boussole);
	
		//moteurs : centrale inertielle+position+vitesse
		//Axe Y(p) provoque une rotation Z(Y) en sens + => il faut compenser en baissant control_p par control_y
		//moteur devant : tête axe X, PWM7
        //moteur2 = /*anc M1(int)(-r_pitch - r_yaw)*/ gas + ( control_p  + control_y );// - (int)control_z;
		//moteur derrière : arriere axe X, PWM3
        //moteur1 = /*anc M2(int)(r_pitch - r_yaw)*/ gas + ( -control_p + control_y );// + (int)control_z;
		//moteur gauche : arriere axe Y, PWM5
        //moteur3 = /*anc M3(int)(r_roll + r_yaw)*/  gas + ( -control_r  - control_y );// + (int)control_x;
		//moteur droit : tete axe Y, PWM1
        //moteur4 = /*anc M4(int)(-r_roll + r_yaw)*/  gas + ( control_r - control_y );// - (int)control_x;

        //moteur1 = initialThurst;
		//moteur2 = initialThurst;
	//	PWMot1 = (unsigned char)sat(moteur1+110,100,180);
	//	PWMot2 = (unsigned char)sat(moteur2+110,100,180);
	//	PWMot3 = (unsigned char)sat(moteur3+110,100,180);
	//	PWMot4 = (unsigned char)sat(moteur4+110,100,180);	//on limite a 180 pour commencer...
		
		
//la commande des moteur est entre 110 et 240 => offset a ajouter
        MCF_PWM_PWMDTY7 = initialThurst;
        MCF_PWM_PWMDTY3 = initialThurst;
        MCF_PWM_PWMDTY5 = initialThurst;
        MCF_PWM_PWMDTY1 = initialThurst;
		/*MCF_PWM_PWMDTY7 = (unsigned char)sat(moteur1+110,100,240);
		MCF_PWM_PWMDTY3 = (unsigned char)sat(moteur2+110,100,240);
		MCF_PWM_PWMDTY5 = (unsigned char)sat(moteur3+110,100,240);
		MCF_PWM_PWMDTY1 = (unsigned char)sat(moteur4+110,100,240);	//on limite a 180 pour commencer...*/
	

		cpt_ech++;			//compteur d'echantillons
		if(cpt_ech>99)
		{
			cpt_ech=0;
			//printf("GAS=%d, PWMot1,2,3,4=%d,%d,%d,%d\n",gas,PWMot1,PWMot2,PWMot3,PWMot4);
			/*printf("MoyAX,MoyAY=%d,%d  VAX,VAY,VAZ=%d,%d,%d   AAX,AAY,AAZ=%d,%d,%d\n",MoyAX,MoyAY,VAX,VAY,VAZ,AAX,AAY,AAZ);
			printf("control_r,p,y=%d,%d,%d\n",control_r,control_p,control_y);
			printf("moteurs 1,2,3,4=%d,%d,%d,%d\n\n",moteur1+110,moteur2+110,moteur3+110,moteur4+110);*/
		}
/* Test clavier */
		if (kbhit())
			{
				choix = getch();	//lire derniere touche appuyee
				switch (choix)
				{
				case '+':
					//if (initialThurst < 200) initialThurst+=5;
					printf("initialThurst=%d\n",initialThurst);
					break;
				case '-':
					//if (initialThurst > 120) initialThurst-=5;
					printf("initialThurst=%d\n",initialThurst);
					break;
				case 's':
					//initialThurst = 110;
					printf("Setting motors to initial value %d \n",initialThurst);
					break;
				/*case 'V':
					GvX++; GvY++;
					printf("Gv=%d\n",GvX);
					break;
				case 'v':
					if (GvX>1)
					{
						GvX--; GvY--;
					}
					printf("Gv=%d\n",GvX);
					break;
				case 'A':
					GaX++; GaY++;
					printf("Ga=%d\n",GaX);
					break;
				case 'a':
					if (GaX>1)
					{
						GaX--; GaY--;
					}
					printf("Ga=%d\n",GaX);
					break;
				case 'Z':
					GvZ++;
					printf("GvZ=%d\n",GvZ);
					break;
				case 'z':
					if (GvZ>1)
					{
						GvZ--;
					}
					printf("GvZ=%d\n",GvZ);
					break;
				case 'p':	//c'est variable inverse
					IGpX++; IGpY++;
					printf("IGp=%d\n",IGpX);
					break;
				case 'P':
					if (IGpX>1)
					{
						IGpX--; IGpY--;
					}
					printf("IGp=%d\n",IGpX);
					break;*/
				case (27):
				case (10):		// Arret d'urgence
					MCF_PWM_PWMDTY1 = 0;	//couper les PWM
					MCF_PWM_PWMDTY3 = 0;
					MCF_PWM_PWMDTY5 = 0;
					MCF_PWM_PWMDTY7 = 0;
					return(0);
					break;
			
				}
			}
	}		
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
	MCF_DTIM0_DTMR=0x501B; //RAZ auto, pas de prediv 16, IT
	MCF_DTIM0_DTRR=19999; //Registre Reference pour 100Hz
	MCF_DTIM0_DTCN=0; //RAZ registre Compteur
	MCF_DTIM0_DTER=0x03; //RAZ registre Drapeaux

	//MCF_INTC_ICR1 = 0xB0000000;
	//MCF_INTC_ICR19 = MCF_INTC_ICR_IL(0x4);
	MCF_INTC_ICR19 = MCF_INTC_ICR_IL(0x5);
	MCF_INTC_IMRL = MCF_INTC_IMRL & ~(MCF_INTC_IMRL_MASK19);
	//MCF_INTC_ICR44 = MCF_INTC_ICR_IP(0x7);
	io_32(ADR_VECT_INT0) = (long)isrINT0; // Chargement du vecteur d'interruption dans la table
	__asm("move.w #0x2200,%sr\n");	 // Initialisation a 2 du masque de priorite d'interruption dans le registre d'etat	
	
	//MCF_INTC_ICR_IL
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

/*int sat(int value, int min, int max)
{
	int retour;
	if (value>max)	retour=max;
	else if (value < min) retour=min;
		 else retour=value;
	return (retour);
}*/

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


