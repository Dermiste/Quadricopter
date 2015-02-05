/* Fonctions de base utilisant DBUG */

#include "main.h"


void out_char(int ch);
void out_byte(int ch);

/*****************/
int kbhit( void )
/*****************/
{
	return ( MCF_UART0_USR & MCF_UART_USR_RXRDY );
}

/**************/
int getch(void)
/**************/
{
	/* Wait until character has been received */
	while (!(MCF_UART0_USR & MCF_UART_USR_RXRDY));
	return (MCF_UART0_URB & 0xFF);
}
/*
int putchar(int ch)
{
	out_char(ch);
	return 1;
}
*/
	/************************/
	/*   Fonction outcar	*/
	/************************/
/*
	Cette fonction est associée à la fonction mfprintf
*/
void out_char(int ch)
{
    if ( ch == '\n')
        out_char('\r');

	/* Wait until space is available in the FIFO */
	while (!(MCF_UART0_USR & MCF_UART_USR_TXRDY));

	/* Send the character */
	MCF_UART0_UTB = ch;
}


void out_byte(int ch)
{
	/* Wait until space is available in the FIFO */
	while (!(MCF_UART0_USR & MCF_UART_USR_TXRDY));

	/* Send the character */
	MCF_UART0_UTB = ch;
}


/***************************/
int puts(const char * text )
/***************************/
{
	while ( * text )
	{
		out_char(* text);
		text++;
	}
    
    out_char('\n');     // Le compil enleve le dernier \n
	return 1;
}
