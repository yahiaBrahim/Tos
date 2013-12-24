/*!
 * summary :functions in this file are used as an intermadiate between the shell command and the 		system function (system calls) this is useful to perform some security tests, for 		exemple check and test if the parameters passed are secure
 * version : 0.2
 * last modification : 31/08/2007 by baghdadi
 * authors :Baghdadi Mohamed
 * emails  : Baghdadi13 [AT]  gmail.com
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */
 
 
#include "console.h"



void shellExit(short EXIT_STATUS)
{
	printf("\nyou cannot exit");
}



/*! 
* this function is called when a command is not found
*/
void CmdNotImplemented()
{
	printf("\nunknown Command.\nTo add a new command :\n");
	printf("-add it's corresponding function to  the file consoleFunctions.c \n");
	printf("-add the command itself to the function initUCT(),");
	printf("(commands in the function initUCT() are sorted by alphabetic order.");
	listUCTCmd();
}



void listUCTCmd()
{
int i=0;

printf("\nCommands are :");
for (i=0; i<UCT_CMD_NUMBER; i++)
{
	if(i%5 == 0) 	  printf("\n");    	//a new line for each 5 commands
	printf(UCT[i].cmd_name);		//print the command
	printf("\t");
}
printf("\nFor more information read the Documentation");
}


/*!
 print a string on the screen
*/
void echo(char * str)
{
	printf("\n");
	printf(str);
}


