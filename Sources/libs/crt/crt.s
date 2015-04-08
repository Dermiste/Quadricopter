/*
#	crt.s: startup pour kit coldfire 5213 sous DBUG
#	---------------------------------------------------------------
*/
	.file	"crt.s"
	XDEF	start
	XDEF	_start
/*.xref end, __bss_start	/* predefini par le linker, debut et fin de section BSS */
	ALIGN	4


start:
_start:

    nop                     /* Debuggers may object to starting at 0.*/

/*    move.l  #(__SP_INIT),%a7	 Initialize stack pointer %a7 to value in linker command file.*/
	
/* raz BSS section */
	move.l #__BSS_START, %a0;
	move.l #__BSS_END, %d0;

clr_bss_ram:
	cmp.l %a0, %d0
	beq start_main
	clr.b (%a0)+
	jmp clr_bss_ram
 
start_main: 
    jsr     main

/* end_main: jmp end_main */
    clr.l %d0
    trap #15    /* Retour a DBUG */

#------------------------------------------------------------- .init section --
	XDEF	__init		            
__init:			                /* Entry to ___init, called by ___init_main called above.*/

	# Linker places .init sections from other modules, containing
	# calls to initialize global objects, here.

	rts			                    /* Return from ___init. */

#------------------------------------------------------------- .fini section --
	XDEF	__fini
__fini:			                /* Entry to ___fini, called by exit(). */

	# Linker places .fini sections from other modules, containing
	# calls to destroy global objects, here.

	rts			                    /* Return from ___fini.*/
