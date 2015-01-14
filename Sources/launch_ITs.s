/* __________________________________________________________________
 * 
 * Fichier:	launch_ITs.s pour COBRA5272 
 * Auteur(s):	O.L.
 * Compagnie:	IUT1 de Grenoble, Dpt GEII2	
 * Contenu:	Code assembleur pour appeler les fct C d'interruption
 * Version:	1.0
 * Date:	02/03/07
 * __________________________________________________________________
 * CHANGEMENTS
 *
 * 14/10/14	V.G. : Adaptation pour INT1
 * __________________________________________________________________
 *
 * Quand l'interruption survient et qu'elle est autorisee, ce bout
 * de code assembleur est execute. Il sauve le contexte, appelle
 * la routine d'interruption C ActionINT1(), restore le contexte et
 * retourne au main() grace a 'rte'.
 * __________________________________________________________________
 */

.global isrINT0		| Pour que cette etiquette soit vu par le linker
.extern actionINT0	| Pour pouvoir appeler cette fct C depuis l asm 

/* ----------------------------------------- */
/* --- Section du code et des constantes --- */
/* ----------------------------------------- */
.text

isrINT0:	
| Sauvegarde du contexte integral pour appel de la fonction C
        sub.l		#4*15, %A7
		movem.l		%D0-%D7/%A0-%A6,(%A7)

| Appel de la fonction C de traitement de l'interruption
		jsr		actionINT0
		
| Restauration du contexte integral
		movem.l		(%sp),%d0-%d7/%a0-%a6
		add.l		 #4*15, %A7
		
| Retour d'interruption
		rte

/* ------------------------------------------- */
/* --- On peut ajouter d autres fcts d ITs --- */
/* ------------------------------------------- */


.end
