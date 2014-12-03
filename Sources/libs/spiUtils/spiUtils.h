#include "../mcf5213/mcf5213.h"

#ifndef __SPI_UTILS__
#define __SPI_UTILS__

#define WHO_AM_I 0x0F
//Registres accelero LIS331 et Gyro L3G4200
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

#define	CSG_ON MCF_GPIO_CLRUA=0xF7 		// Activation du CS gyro
#define	CSG_OFF MCF_GPIO_SETUA=0x08 	// DeActivation du CS gyro
//CS Acc sur PQS4
#define	CSA_ON MCF_GPIO_CLRQS=0xEF 		// Activation du CS Acc
#define	CSA_OFF MCF_GPIO_SETQS=0x10		// DeActivation du CS Acc

#define __IPSBAR ((volatile unsigned char*)(0x40000000))

char Init_AccGyro (void);
void Init_spi (void);
void SpiWrite8 (unsigned char ad, unsigned char datawrite);
void SpiRead6R(char* buffer);
char SpiRead8 (unsigned char ad);

#endif /* __SPI_UTILS__ */