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



#include "mfs.h"			//memory file system header file
#include  "../../kern/memory/memory.c"	//for malloc, memcopy ...
#include  "../../libc/types.h"


/*!
 * fread : read a bloc of bytes from the file f, after reading the cursor changes to the next non read byte, fread doesnt return an error code if you read outside the file
 * */
void fread (int * data ,size_t size, size_t nbloc, struct FILE * f)
{
	int i=0;	//used as an index
	while( !eof() && (i < (size*nbloc)) )
	{
		*(data +i)= f->cur_adr;
		(f->cur_adr)++;
		(f->cur)++;
		i++;
	}
}


/*!
 * eof : return true if the next byte to be read is not part of the file (outside the file)
 * */
int eof(struct FILE * f)
{
	if ( (*f).cur_adr == (*f).eof_adr)  //this is the end of the file
		return 1; //true
	else
		return 0; //false
}


/*!
 * fwrite : write a bloc of bytes into a file, after writing the cursor is autoadjusted to the new position
 **/
void fwrite (u8 * data,size_t size, size_t nbloc, struct FILE * f)
{
	


}


/*!
 * fopen: open a file, and put the cursor in the beginning of the file
 * */
struct FILE * fopen(char * name, char * mod)
{

}


/*!
 * fclose : close the file f
 * */
void close(struct FILE * f)
{

}
















