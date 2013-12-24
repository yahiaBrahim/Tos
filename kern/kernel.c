/*!
 * summary : 
 * version : 0.3
 * last modification : 31/08/2007
 * authors : Djekidel Mohamed Nadhir  	, Baghdadi Mohamed
 * emails  : djek_nad [at] yahoo.com 	, Baghdadi13 [at] gmail.com*/
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */
#include "multiboot.h"
#include "../kernel_components/libc/stdio.c"
#include "../kernel_components/console/logo.c"
#include "idtloader.c"
#include "KeybordDriver.c"
#include "IrqHandler.c"
#include "../kernel_components/libc/string.h"
#include "../kernel_components/console/console.c"
#include "./memory/gdt.c"

extern void ChargerIDT(); 

/*void _start(void)
{
   main();
} */    
  
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit))) 
/*! main kernel entry*/
int main(unsigned long magic, unsigned long addr) 
{
    
   multiboot_info_t *mbi;
   mbi = (multiboot_info_t *) addr;
  
   printf ("Addr of Muktibootinfo: 0x%x \n", mbi);
   char cmd[256];    
 if (magic == MULTIBOOT_BOOTLOADER_MAGIC)
         {
           printf ("Valid magic number: 0x%x\n", (unsigned) magic);
          
         }  


	
/*	logo(); 	*/
printf ("flags : 0x%x \n", mbi->flags);
if (CHECK_FLAG (mbi->flags, 6))
         {
          printf ("Memory map is Valid \n");       
  
          multiboot_memory_map_t *mmap;
                
           printf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
          (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
           for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
                (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
                mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
                                         + mmap->size + sizeof (mmap->size)))
             printf (" size = 0x%x, base_addr = 0x%x%x,"
                     " length = 0x%x%x, type = %d\n",
                     (unsigned) mmap->size,
                     mmap->addr >> 32,
                     mmap->addr & 0xffffffff,
                     mmap->len >> 32,
                     mmap->len & 0xffffffff,
                     (unsigned) mmap->type);
         }
     




/*	printf("\nKernel Loaded ..........................");
    	setTextColor(2);
	printf("[OK]\n");	
	setTextColor(7); */
	
	GDT_init();
/*	printf("GDT Loaded .............................");
    	setTextColor(2);
	printf("[OK]\n");
	setTextColor(7);
*/	
/*	printf("Initializing interuptions...............");
*/	
        InitIDT(); 	
/*	setTextColor(2);
	printf("[OK]\n");	
	setTextColor(7);
*/
	ChargerIDT();		
/*	printf("IDT Loaded .............................");  
	setTextColor(2); 
	printf("[OK]\n\n");
*/ 	
  	LoadConsole();			//loads the basic console
  	
  	
  	//we should never get here
}  
