/* Fichier startc.s de demarrage d'un programme ecrit en C - 6 Juillet 1995 */


/* Choix de la pile du microprocesseur par definition du symbole PILE,
	et du tas (au dessus de la pile)
*/
/* PILE  = 0x30000 */
__HEAP_START = PILE+4
__HEAP_END = 0x50000

/* Declaration de variables definies par le linker */
	.extern   main
	.extern __bss_start
	.extern _end

/* Variables ou etiquettes a rendre publique (ou globale) */
	.global   _start, _exit
	.global __HEAP_START, __HEAP_END	/* utilise en malloc */

/* Codage du programme */
	.text
	.align 1     /* alignement sur adresse paire */

_start:

/*	move.l #PILE, %A7    initialisation de la pile */
	

/* remise a zero des variables non initialisees */
	move.l #__bss_start,%A0		/* __bss_start est une etiquette */
					/* definie par le linker */
	move.l #_end,%A1	/* idem pour _end */

raz_variables:		/* remise a 0 de la zone RAM de __bss_start */
				/* a _end */
	cmp.l %A0,%A1
	beq suite
	move.b #0,(%A0)+
	jmp raz_variables

suite:
	jsr    main	/* appel de la fonction principale */

_exit:		/* Fonction exit() */
	move.l #0x0000,%D0
	trap	#15	/* Fin du programme C: retour au moniteur DBUG */


.globl __main
__main:	/* fonction auxiliaire appelee par le compil c */
		/* a chaque appel de routine (cette fonction ne fait ici */
		/* rien d'utile, mais elle pourrait etre completee a des fins*/
		/* de mise au point) */
	rts

	.end
