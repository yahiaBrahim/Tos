/*!
 * summary : describe errors;
 	this file contains some functions that hundle errors , erro messages are put in a 
 *	separate file so that you can change the language of these messages easily, to change 
 *	the language of these message just change the header file
 * version : 0.1
 * last modification : 21/07/2007
 * authors : Baghdadi Mohamed
 * emails  : Baghdadi13 [AT]  gmail.com
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */


 
#include "msgEn.txt"				//error messages file

#define ERRORS_COUNT 20				//20 error message

 char * errorTable[ERRORS_COUNT] = {
 					ERR_BOOT_ERROR,
 					ERR_FILE_NOT_FOUND,
 					ERR_CMD_NOT_FOUND
 				   };
 
 
 
 /*!
 * input : error number
 * output: the error msg 
 */
 char * getErrorMsg(char errorNumber)
 {
 	return errorTable[errorNumber];
 }
 
 
