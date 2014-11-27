#include "../mcf5213/mcf5213.h"
#define __IPSBAR ((volatile unsigned char*)(0x40000000))
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

void Init_spi (void);
void SpiWrite8 (unsigned char ad, unsigned char datawrite);
void SpiRead6R(char* buffer);
char SpiRead8 (unsigned char ad);