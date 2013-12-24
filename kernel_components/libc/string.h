/*!	string.h : string Library header
	version  : 0.3
	date     : 24/08/2007
	author	 : Baghdadi Mohamed  
	 * emails  : Baghdadi13 [AT]  gmail.com
	last editor : baghdadi (31/08/2007)
	
*/

#ifndef _HEADER_STRING_C
#define	_HEADER_STRING_C

#include "types.h"		//Types definition

#define END_CHAR  '\0'		//char indicates the end of string
#define LINE_LENGTH 255		//length of a line in the console
#define MAX_LINE_CHAR	254	//used as LINE_LENGTH-1, but it's calculated for performence

#include "string.c"		//implementation of the functions

char * strcat(char * destination,char * source);
char * strchr(char * s,int c);
int strcmp(char * s1,char * s2);
inline char * strcpy(char  s1[], const char s2[]);
size_t strlen(const char * s);
char * Sreadline();
char * readline();

#endif
