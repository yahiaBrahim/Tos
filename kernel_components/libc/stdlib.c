/*
 * summary : stdlib.h : The stdlib file defines several general operation functions
 * version : 0.1
 * last modification : 08/09/2007
 * authors : Baghdadi Mohamed
 * emails  : Baghdadi13 [AT]  gmail.com
 * -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */


/* official functions of the math.C library :
abs();----------------------- ok
atoi();-----------------------convert the result of atol (which is long) to an integer
atol();-----------------------ok
calloc();
div();
exit();
free();
getenv();
malloc();
rand();
realloc();
srand();
system();
*/

#include "ctype.c"

#ifndef _HEADER_STDLIB_C
#define	_HEADER_STDLIB_C

/*!
 * str ---> long
 * The string pointed to by the argument str is converted to an integer (type long). Any initial space 
 * characters are skipped . this function doesn't deal with negative signe
 * Conversion stops when the first unrecognized character is reached.
 * On success the converted number is returned. If the number cannot be converted, then 0 is returned.
*/
unsigned long atol(const char * str)
{
	register int result=0;
	
	while(isdigit(*str))
	{
		result = (result*10) + (*str)-'0';
		str++;
	}
	if( !isdigit(*str) && (*str != '\0')) 	//error , we are out of the while before we get the end of str
		return -1;
	else					//no error
		return result;
}




/*!
 * Returns the absolute value of x, (a negative value becomes positive, positive value is unchanged).
 * */
int abs(int x)
{
	if(x<0) x = x * (-1);
	return x;
}

#endif
