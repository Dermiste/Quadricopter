#include "spiUtils.h"

void Init_spi (void)
{
	//Proprietes du transfert SPI
	MCF_QSPI_QMR = 0xA308;		//tfert 8 bits, CPOL=1, CPHA=1 fclk=1Mhz
	MCF_QSPI_QDLYR = 0x0000;   	//Activation du  bus SPI   //////>>   pour init un transfert mettre 0x8000
	MCF_QSPI_QWR = 0x0000;     	//Pointeurs de la RAM (FIFO limitee a un mot)    
	MCF_QSPI_QIR = 0xD00D;     	//Drapeau fin de transfert
	MCF_QSPI_QAR = 0x0020;		//selection RAM de commande
	MCF_QSPI_QDR = 0x0E00;		// A  defaut
	
	// init des CS Gyro et accelero	
	MCF_GPIO_SETQS=0x08;		// mise à niveau haut du CS gyro	
	MCF_GPIO_DDRQS|=0x08;		// CS du gyro mis en sortie
	MCF_GPIO_SETQS=0x10;		// mise à niveau haut du CS acc	
	MCF_GPIO_DDRQS|=0x10;		// CS de l'accéléro mis en sortie
	MCF_GPIO_SETQS=0x20;		// mise à niveau haut du CS acc	
	MCF_GPIO_DDRQS|=0x20;		// CS de l'accéléro mis en sortie
	MCF_GPIO_SETQS=0x40;		// mise à niveau haut du CS acc	
	MCF_GPIO_DDRQS|=0x40;		// CS de l'accéléro mis en sortie	
}

char Init_sensors (void)
{

	unsigned char gyro_value, acc_value, baro_value;


	CSG_ON;
		SpiWrite8(ST_CTRL_REG1,0x08); // power down first
	CSG_OFF;

	CSG_ON;
		SpiWrite8(ST_CTRL_REG1,0xBF);//0b1011.1111
	CSG_OFF;
	
	CSG_ON;
		SpiWrite8(ST_CTRL_REG2,0x08);
	CSG_OFF;
	
	CSG_ON;
		SpiWrite8(ST_CTRL_REG4,0x10);
	CSG_OFF;

	CSG_ON;
		gyro_value=SpiRead8(ST_WHO_AM_I);
	CSG_OFF;	
	

	CSA_ON;
		SpiWrite8(ST_CTRL_REG1,0x67);// 0x67	 //Mode normal, data rate 100Hz, en all axis, LP  74Hz
	CSA_OFF;	

	CSA_ON;
		SpiWrite8(ST_CTRL_REG5,0x74); // 74
	CSA_OFF;


	CSA_ON;
		SpiWrite8(ST_CTRL_REG6,0x00);
	CSA_OFF;

	CSA_ON;
		SpiWrite8(ST_CTRL_REG7,0x00);

	CSA_OFF;

	CSA_ON;
		acc_value=SpiRead8(ST_WHO_AM_I);
	CSA_OFF;

	CS3_ON;
		SpiWrite8(ST_CTRL_REG1,0xC0);
	CS3_OFF;

	CS3_ON;
		baro_value = SpiRead8(ST_WHO_AM_I);
	CS3_OFF;

	printf("Acc value: 0x%x, Gyro value: 0x%x, Baro value: 0x%x\n", acc_value, gyro_value, baro_value);		

	if ((acc_value != 0x49) || (gyro_value !=0xd3) || (baro_value !=0xbd)){
		return(0);
	} else {
		return(1);
	} 
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

void SpiRead6R(char startAddress, char* buffer)
{
	unsigned char reg;
	MCF_QSPI_QIR = 0xD00D;	//RAZ SPIF
	//Transfert du premier mot = code fonction
	MCF_QSPI_QAR = 0x0000;			//On se place au niveau de l'envoi dans la RAM : transmit RAM
	MCF_QSPI_QDR = startAddress | 0xC0; 	//On envoie le code fonction (8 bits) avec mise a 1 bit R/W et M/S
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

void SpiListSlaves(){
	unsigned char who_am_i,i;
	char message[40] = "Slave ID %d in slot %d";
	for (i=0;i<4;i++){
		MCF_GPIO_SETQS = (0x08 << i) ;
			who_am_i=SpiRead8(ST_WHO_AM_I);
			printf(message, who_am_i & 0xFF, i);
		MCF_GPIO_CLRQS = ~(0x08 << i) ;

	}
}


