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



/* official c library functions :
isalnum();------------------------- noneed
iscntrl();------------------------- noneed
isdigit();------------------------- ok
isgraph();------------------------- noneed
isprint();------------------------- noneed
isupper();------------------------- noneed

isxdigit();
islower();
isspace(); 
isalpha();
tolower();
toupper();
*/



#ifndef _HEADER_CTYPE_C
#define	_HEADER_CTYPE_C


/*!
 * returns true if the char c is a digit ('0' to '9')
 * */
short isdigit(char c)
{
	if ((c >= '0') && (c <= '9')) return 1;
	else return 0;
}




#endif
