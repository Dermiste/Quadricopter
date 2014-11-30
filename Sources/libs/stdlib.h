/*
 * File:		stdlib.h
 * Purpose:		Function prototypes for standard library functions
 *
 * Notes:
 */

#ifndef _STDLIB_H
#define _STDLIB_H

/********************************************************************
 * Standard library functions
 ********************************************************************/
int kbhit(void);
int getch(void);
int putchar(int ch);
int	printf(const char *, ... );

int isspace (int);

int isalnum (int);

int isdigit (int);

int isupper (int);

int strcasecmp (const char *, const char *);

int strncasecmp (const char *, const char *, int);

unsigned long strtoul (char *, char **, int);

int strlen (const char *);

char * strcat (char *, const char *);

char * strncat (char *, const char *, int);

char * strcpy (char *, const char *);

char * strncpy (char *, const char *, int);

int strcmp (const char *, const char *);

int strncmp (const char *, const char *, int);

void * memcpy (void *, const void *, unsigned);

void * memset (void *, int, unsigned);

void free (void *);
 
void * malloc (unsigned);

/********************************************************************/

#endif
