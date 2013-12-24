
/*
 *	errors.h : describe errors;
 *	version  : 0.1
 *	Date     : 21/07/2007
 *	this file contains some functions that hundle errors , erro messages are put in a 
 *	separate file so that you can change the language of these messages easily, to change 
 *	the language of these message just change the header file
 */
 
#include "../text/msgEn.txt"				//error messages file

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
 
