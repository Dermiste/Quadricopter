
#ifndef NULL
#define NULL (void*)0
#endif

/*******************************************/
char * strcpy (char *dest, const char *src)
/*******************************************/
{
	char *dp = (char *)dest;
	char *sp = (char *)src;

	if ((dest != NULL) && (src != NULL))
	{
		while (*sp != '\0')
		{
			*dp++ = *sp++;
		}
		*dp = '\0';
	}
	return dest;
}

	/***********************************************************/
	/* Fonction mfprinf, analogue a printf, pour upro Coldfire */
	/***********************************************************/

/* Affiche ce que l'on souhaite sous dbug pour la carte d'expérimentation*/
/* 			Utilisation de la fonction mfprintf:
						mfprintf(fct specifique,...)

	fct specifique : utilisez out_car pour la carte Coldfire
	... : syntaxe équivalente à la fonction printf

	exemple: mfprintf(out_car,"Salut %s, nous sommes en %d.\n","toi",2006);
	affiche : Salut toi, nous sommes en 2006.

										*/
/*		fichier MFPRINTF.C		*/

//#include <string.h>
#include <stdarg.h>
//#include <ctype.h>


	/************************/
	/*   Fonction out_car	*/
	/************************/
/*
	Cette fonction est associée à la fonction mfprintf

*/

const char chiffre[16] = {'0','1','2','3','4','5','6','7','8','9',
						'a','b','c','d','e','f' } ;

#define isdigit(val) ((val) >= '0' && (val) <= '9')

int strlen(char * text)
{
	int ii = 0;
	while ( * (text++) ) ii++;
	return ii;
}
/* fonctions locales :*/

void itoa( int k , char* tmp , int base )
{
char signe , * ptchar ;

	ptchar = tmp ; signe = 0 ;
	if ( k < 0 ) { signe++ ; k = -k ; }
	if (base == 10 )
		do  {
			*(tmp++) = chiffre[k % 10] ; k /= 10 ;
			} while (k) ;

	else /* base = 16 */
		do  {
			*(tmp++) = chiffre[k & 15] ; k >>= 4 ;
			} while (k) ;

	if(signe != 0 ) *(tmp++) = '-' ;
	*tmp = 0 ; tmp-- ;
	/* reclassement en ordre inverse */

	while ( ptchar < tmp)
		{
		signe = *ptchar ; *ptchar = *tmp ; *tmp = signe ;
		ptchar++ ; tmp-- ;
		}
}

void ultoa( unsigned long k , char* tmp , int base ) 
{
char * ptchar, ctmp  ;

	ptchar = tmp ;
	if ( base == 10)
		do  {
			*(tmp++) = chiffre[k % 10] ; k /= 10 ;
			} while (k) ;

	else /* base = 16 */
		do  {
			*(tmp++) = chiffre[k & 15] ; k >>= 4 ;
			} while (k) ;

	*tmp = 0 ; tmp-- ;
	/* reclassement en ordre inverse */
	while ( ptchar < tmp)
		{
		ctmp = *ptchar ; *ptchar = *tmp ; *tmp = ctmp ;
		ptchar++ ; tmp-- ;
		}
}

	/**************/
	/* mfprintf() */
	/**************/

/*
equivalent de la fonction printf pour uprocesseurs
fait appel a la fonction void out_char(char code) , fonction de sortie
du code ascii sur le perif desire .

syntaxe :
mfprintf(void out_char() ,(const char *)format,...)
	avec :
	format = pointeur sur chaine .
	... = "valeurs" a imprimer .

	descripteurs :
	%[flags][nbcar][.precision][prefix]type.

	flag = + => justifcation a droite (normale)
		- =>	 "       … gauche
	nbcar = nombre minimum de chiffres
	.precision = nombre max de caracteres

	prefix = l (long)
	type =
		d : decimal sign‚
		i : decimal sign‚
		u : d‚cimal non sign‚
		x : hexadecimal ( utilisant abcdef)
		X : hexadecimal ( utilisant ABCDEF)
		c : code ascii (donne en entier )
		s : chaine de caractere .
*/

/* liste des codes de description de formats */
const char code_descr[22] = {'0','1','2','3','4','5','6','7','8','9',
		'l','u','d','i','x','X','c','s','+','-','.', 0 };

/* type interne des codes de description
(permet de regrouper les cas de traitement */
const char code_type[] = { 1,1,1,1,1,1,1,1,1,1,		/* chiffres */
			 2,				/* prefix */
			 9,				/* unsigned */
			 3,3,				/* decimal */
			 4,4,				/* hexadecimal */
			 5,				/* code ascii */
			 6,				/* chaine de caractere */
			 7,7,				/* flags */
			 8 ,				/* precision */
			 0 };				/* non reconnu */


//void mfprintf(void out_char() , const char *format, ...)
void printf( const char *format, ...)
{
va_list pt ;		/* pt = pointeur sur les arguments optionnels */
int i , j , k , nbcar , precision , base  ;
long kl ;
char flag , prefix , type , *ptcar , tmpcar ;
char tmp[20] ;

	va_start(pt,format) ;	/* init pointeur sur premier argument */
	
	while ( *format != 0 )
	{
		if (*format != '%' )
		{
			out_char(*format) ;
//            if (*format == '\n') out_char('\r') ; dans out_char maintenant
		}
	
		else	/* descripteur de format trouve ! */
		{
			/* ajustement des parametres par defaut : */
			nbcar = 0 ;precision = 0 ;flag = '+' ;prefix = 0 ;format++ ;
	
			/* recherche du type de descripteur */
		traitement_descripteur:
			base = 10 ; i = 0 ; j = 0 ;
			while( ((tmpcar = code_descr[j]) != *format) && (tmpcar != 0)) j++ ;
	
			switch ( code_type[j] )	  /* type trouv‚ : */
			{
				case 0 : 	/* code inconnu */
					out_char(*format);
					break;
	
				case 1 :	/* width (nb mini de caract) */
				{
					 while (isdigit(*format))
					{
						nbcar *= 10 ; nbcar += *format - '0' ;
						format++ ;
					}
					 goto traitement_descripteur ;
					}
	
				case 2 :	/* prefixe trouv‚ */
				{
					prefix = *format ;
					format++ ; goto traitement_descripteur;
				}
	
				case 4 :	/* hexadecimal (donc unsigned) */
					base = 16 ;
				case 9 :	/* unsigned */
				{
					if ( prefix != 'l')	kl=(unsigned)va_arg(pt,int);
					else kl = (unsigned)va_arg(pt,long);
					ultoa( kl , tmp , base ) ;
					goto sortie_nombre ;
				}
	
				 case 3 :		 /* integer */
				{
					if ( prefix != 'l')
					{
						k = va_arg(pt,int) ; itoa( k , tmp , base ) ;
					}
					else
					{
						kl = va_arg(pt,long) ; ultoa( kl , tmp , base ) ;
					}
	
				sortie_nombre :
					precision -= strlen(tmp) ;
					if (tmp[i] == '-') out_char(tmp[i++]) ;
					while ( precision-- > 0 ) out_char('0') ;
					while(tmp[i] != 0)
					{
						if ( (*format == 'X') && (tmp[i] >= 'a' ))
								out_char((char)(tmp[i] + (char)('A'-'a'))) ;
						else out_char(tmp[i]) ;
						i++ ;
					}
					break ;
				}
				case 8 :	/* traitement de la precision */
					 {
					 format++ ;
					 while (isdigit(*format))
					{
						precision *= 10 ;
						precision += *format -'0';
						format++ ;
					}
					 if (precision <= 0 ) precision = 1 ;
					 goto traitement_descripteur ;
				}
	
				case 7 : flag = *format ; break ;
	
				case 5 :	   /* sortie de 1 code ascii */
				{
					type = (char) va_arg(pt,int) ;
					out_char(type) ;
					break ;
				}
				case 6 :	/* chaine de caracteres */
				{
					ptcar = (char *) va_arg(pt,char *) ;
					while(*ptcar != 0)
					{
						out_char(*ptcar) ; ptcar++ ;
						if (--precision == 0 ) break ;
					}
					break ;
				}
				default : break ;
			}
		}
		format++ ;
	}
	va_end(pt) ;
	
	out_char(0);	// Place un fin de string
	return ;
}

