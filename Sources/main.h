// main.h
#define __IPSBAR ((volatile unsigned char*)(0x40000000))
#include "libs/mcf5213/mcf5213.h"
#include "libs/registres-ST.h"
#include <stdio.h>

#define __interrupt__ extern
#define FLASHBAR 0xC04
#define RAMBAR 0xC05
#define VBR 0x801


/* --- Prototype des fonctions des modules --- */



/* Module Alim */

void init_alim(void); // Permet l'installation du vecteur d'interruption
extern void batterie(void);

/* Module asservissement */

void init_asservissement(void); // Permet l'installation du vecteur d'interruption
extern void asservissement(void); // Asservissement numérique par interruptions venant de TMR0.



//A définir

/* Interface Homme Machine (hmi.c) */

// A définir
