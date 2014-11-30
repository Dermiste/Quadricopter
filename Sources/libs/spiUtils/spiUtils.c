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
	MCF_QSPI_QDR = OUT_X_L | 0xC0; 	//On envoie le code fonction (8 bits) avec mise a 1 bit R/W et M/S
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