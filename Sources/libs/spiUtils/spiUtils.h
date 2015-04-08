#include "../mcf5213/mcf5213.h"
#include "../registres-ST.h"

#ifndef __SPI_UTILS__
#define __SPI_UTILS__

#define __IPSBAR ((volatile unsigned char*)(0x40000000))

#define	CSG_OFF MCF_GPIO_SETQS=0x08 
#define	CSG_ON  MCF_GPIO_CLRQS=0xF7 		

#define	CSA_OFF MCF_GPIO_SETQS=0x10		
#define	CSA_ON  MCF_GPIO_CLRQS=0xEF	

#define CS2_OFF MCF_GPIO_SETQS=0x20
#define CS2_ON  MCF_GPIO_CLRQS=0xDF

#define CS3_OFF MCF_GPIO_SETQS=0x40
#define CS3_ON  MCF_GPIO_CLRQS=0xBF


char Init_sensors (void);
void Init_spi (void);
void SpiWrite8 (unsigned char ad, unsigned char datawrite);
void SpiRead6R(char startAddress, char* buffer);
char SpiRead8 (unsigned char ad);

void SpiListSlaves();

#endif /* __SPI_UTILS__ */