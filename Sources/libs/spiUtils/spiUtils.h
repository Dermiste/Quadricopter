#include "../mcf5213/mcf5213.h"
#include "../registres-ST.h"

#ifndef __SPI_UTILS__
#define __SPI_UTILS__

#define	CSG_ON MCF_GPIO_CLRUA=0xF7 		// Activation du CS gyro
#define	CSG_OFF MCF_GPIO_SETUA=0x08 	// DeActivation du CS gyro
//CS Acc sur PQS4
#define	CSA_ON MCF_GPIO_CLRQS=0xEF 		// Activation du CS Acc
#define	CSA_OFF MCF_GPIO_SETQS=0x10		// DeActivation du CS Acc

char Init_AccGyro (void);
void Init_spi (void);
void SpiWrite8 (unsigned char ad, unsigned char datawrite);
void SpiRead6R(char* buffer);
char SpiRead8 (unsigned char ad);

#endif /* __SPI_UTILS__ */