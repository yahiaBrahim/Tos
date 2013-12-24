/*
 *	memory.h : memory library
 *	version : 0.1
 *	20/07/2007
 *	
*/


#include "../../kernel_components/libc/types.h"	//for size_t
#include "allocators/memory_allocator_firstFit.c"

#ifndef _HEADER_MEMORY_C
#define	_HEADER_MEMORY_C

#define ALLOCATOR_BASE 0x100000		//we start allocating memory from this address
void * NextFreeByte=ALLOCATOR_BASE;	//indicates the next free byte in memory

/*!
 * Copies n characters from str2 to str1
 */
void memcopy(void *str1, void *str2, int n)
{
	register char  * source      = str1 ;
	register char  * destination = str2;
	int i;

	for(i=0;i<n;i++)
	{		
		*(destination + i) = *( source + i);	
	}
}

void memset(void *dest,int size,char car)
{
	register char *dist=dest;
	while(size>0)
	{
		*dist++=car;
		size--;		
	};
	
}


/*!
 * copy memory to file, used to write MEM_VIDEO to a file, or used to write to the paging file
*/
int writeMemToFile()
{
	//not yet writen
}


/*!
 * malloc : a simple malloc that allocates the next bytes of memory and return to you their address
*/
void * malloc(size_t size)
{
	return mem_firstFit_alloc(size);
}

void free(void * address)
{
	mem_firstFit_free(address);
}

void memory_allocator_init()
{
	// start at address 2MB
	// memory size = 16MB, this should be set to the size of real memory
	mem_firstFit_init(2000000, 16*1024*1024); 
}

unsigned long int mem_get_free_space()
{
	return mem_firstFit_free_size();
}

#endif
