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
pow();----------------->ok
fabs();---------------->ok
sqrt();-------------- must be implemented
 */
 
 
#ifndef _HEADER_MATH_C
#define	_HEADER_MATH_C
 
 
 
/*!
 * Returns x raised to the power of y  (x and y are integers)
*/ 
double pow(int x,int y)
{
	register int i;
	register long result=1;
	
	for(i=0; i<y; i++)
	{
		result = result * x;
	}
	
	return result;
}



/*!
 * Returns the absolute value of x, (a negative value becomes positive, positive value is unchanged).
 * */
double fabs(double x)
{
	if(x<0) x = x * (-1);
	return x;
}


#endif

