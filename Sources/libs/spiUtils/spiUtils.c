#include "spiUtils.h"

void Init_spi (void)
{
//configuration des broches multifonctions
	MCF_GPIO_PUAPAR &= 0x3F;	// Port UCTS0 en GPIO pour le CS du gyro
	MCF_GPIO_PQSPAR = 0x0015;	//QS4 GPIO(CS Acc), QS3..1 en primary pour SPI	      
	
//Proprietes du transfert
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

char Init_AccGyro (void)
{
	unsigned char gyro_value, acc_value;
//config Gyro CTRL_REG1:
	//ODR=400Hz, Cut-off=110Hz => DR+BW="1011"
	//Tous les axes activés : PD=1, Zen=1, Yen=1, Xen=1
	CSG_ON;
	SpiWrite8(ST_CTRL_REG1,0xBF);//0b1011.1111
	CSG_OFF;
	
	//CTRLREG2:
	//normal mode :0000
	//filtre passe haut =0,1Hz, avec ODR400Hz : 1000
	CSG_ON;
	SpiWrite8(ST_CTRL_REG2,0x08);
	CSG_OFF;
	
	//CTRLREG3 : config defaut =0
	//CTRLREG4 : config FS1-FS0 =01 pour sensibilite=500deg/s (=> Quantum=17,5mdps)
	CSG_ON;
	SpiWrite8(ST_CTRL_REG4,0x10);
	CSG_OFF;
	
	//CTRLREG5 : HPF ?
	CSG_ON;
	SpiWrite8(ST_CTRL_REG5,0x00);//HPF enable : 0x10 
	CSG_OFF;
	
//Config Acc CTRL_REG1:
	CSA_ON;
	SpiWrite8(ST_CTRL_REG1,0x37);	//Mode normal, data rate 400Hz, en all axis
	CSA_OFF;
	//CTRL_REG2 : default value : Filters bypass
	//CTRLREG3: default VAlue, pas d'ITS
	//CTRLREG4 : default value : full scale =+-2g, /!\ continuous update MSB LSB
	//CTRLREG5 : default value : sleep to wake disabled
	CSA_ON;
	acc_value=SpiRead8(ST_WHO_AM_I);
	CSA_OFF;
	CSG_ON;
	gyro_value=SpiRead8(ST_WHO_AM_I);
	CSG_OFF;
	//printf("Who am I ACC=%d\tWho am I Gyro=%d\n",acc_value,gyro_value);
	if ((acc_value != 0x32) || (gyro_value !=0xd3))
		return(-1);
	else return(0);
}

void SpiWrite8 (unsigned char ad, unsigned char datawrite)
{
	MCF_QSPI_QIR = 0xD00D;				//RAZ SPIF
	//Transfert du premier mot = code fonction
	MCF_QSPI_QAR = 0x0000; 				//On se place au niveau de l'envoi dans la RAM : transmit RAM
	MCF_QSPI_QDR = ad; 					//On envoie le code fonction (8 bits)
	MCF_QSPI_QDLYR = 0x8000; 			//On init le transfert (en=1)
	while((MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)==0); //On attend qu'il est termine
	MCF_QSPI_QIR = 0xD00D;				//RAZ Flag
	//Transfert du second mot = donnee
	MCF_QSPI_QAR = 0x0000; 				//On se place au niveau de l'envoi dans la RAM : transmit RAM
	MCF_QSPI_QDR = datawrite; 			//On envoie la Data associee
	MCF_QSPI_QDLYR = 0x8000; 			//On init le transfert
	while((MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)==0); 	//On verifie qu'il est termine
}

void SpiRead6R(char* buffer)
{
	unsigned char reg;
	MCF_QSPI_QIR = 0xD00D;	//RAZ SPIF
	//Transfert du premier mot = code fonction
	MCF_QSPI_QAR = 0x0000;			//On se place au niveau de l'envoi dans la RAM : transmit RAM
	MCF_QSPI_QDR = ST_OUT_X_L | 0xC0; 	//On envoie le code fonction (8 bits) avec mise a 1 bit R/W et M/S
	MCF_QSPI_QDLYR = 0x8000; 		//On init le transfert (en=1)	
	while((MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)==0); 	//On verifie qu'il est termine
	for(reg=0;reg<6;reg++)	//parcourir les 6 registres de donnees d'axes
	{
		MCF_QSPI_QIR = 0xD00D;			//RAZ SPIF
		MCF_QSPI_QDLYR = 0x8000; 		//On init le transfert de reception
		while((MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)==0); 	//On verifie qu'il est termine
		MCF_QSPI_QAR = 0x0010; 					//On se place au niveau de la reception dans la RAM
		*buffer = (unsigned char) MCF_QSPI_QDR; //On recupere la Data recue
		buffer++;
	}
}

char SpiRead8 (unsigned char ad)
{
	unsigned char dataread;
	MCF_QSPI_QIR = 0xD00D;	//RAZ SPIF
	//Transfert du premier mot = code fonction
	MCF_QSPI_QAR = 0x0000;			//On se place au niveau de l'envoi dans la RAM : transmit RAM
	MCF_QSPI_QDR = ad | 0x80; 		//On envoie le code fonction (8 bits) avec mise a 1 bit R/W
	MCF_QSPI_QDLYR = 0x8000; 		//On init le transfert (en=1)	
	while((MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)==0); 	//On verifie qu'il est termine
	MCF_QSPI_QIR = 0xD00D;			//RAZ SPIF
	MCF_QSPI_QDLYR = 0x8000; 		//On init le transfert de reception
	while((MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)==0); 	//On verifie qu'il est termine
	MCF_QSPI_QAR = 0x0010; 					//On se place au niveau de la reception dans la RAM
	dataread = (unsigned char) MCF_QSPI_QDR; //On recupere la Data recue
	return(dataread);
}