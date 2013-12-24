/*!
 * summary : In Memory File System : in memory file system  is a complete file system designed to be resident all the time in memory, we can write, read, copy and delete file and use it as a normal file system on the disk, this type of file systems is used mainly in diskless embeded systems or simply because memory is large enough to hold our files
 * version : 0.1
 * last modification : 01/01/2008
 * authors : Baghdadi Mohamed Riyadh
 * emails  : Baghdadi13 [AT]  gmail.com
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */

#include  "../../kern/memory/memory.c"	//for malloc, memcopy ...
#include  "../../libc/types.h"

#ifndef _H_MEMORY_FS
#define _H_MEMORY_FS

//file structure : all needed information on a file
struct FILE
{
	char * adr;		//the file beginning address in memory
	char * cur_adr;		//the cursor address ,
	size_t cur;		//the cursor position in the file : 0 for the beginning of the file
	char * eof_adr;		//the address of the end of file:w
};


#endif
