/*
 * summary : gdt.c : GDT is the global descriptor table, this file contains some
   functions that make GDT manipulation easier. 
 * version : 0.1
 * last modification : 13/10/2007
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

#include "../../kernel_components/libc/types.h" 

/*
1-gdtdescriptor structure : the feilds of a gdt descriptor
2-gdt itelf is an array of gdtdescriptors, it contains all the gdtdescriptors
3-gdtpointer is a structure that indicates the place of the gdt in memory, this pointer is needed by the gdt register,
*/

#define GDTSIZE 16 	//only 16 segments are mapped by the GDT
 
 
/*!	
 * gdtDescriptor :  each gdt descriptor represents a segment in memory
 */
typedef struct gdtDescriptor
{
	u16 segmentLimit_0_15;	//the first 16bit of the segment limit (its length)
	u16 segmentBase_0_15;	//the first 16bit of the segment Base (its beginning)
	u8  segmentBase_16_23;	//8bits in the midle for the segment base (its length)
	u8  segmentType : 4;	//data segment or code segment or stack segment
	u8  segmentOrSystemCall :1;//to revise the name of this after you know what it does
	u8  Ring:2;	//ring0 is kernel segment and ring=3 for user mode segment,this used for protection
	u8  presentOrSwaped:1;	//to indicate if the segment is present in memory or it has been swaped to the HDD
	u8  segmentLimit_16_19:4;
	u8  NotUsed:2;		//this 2 bits feild is not used , so just put it to 0
	u8  instructionSize:1;	//instructionSize=1 for 32bit instructions
	u8  limitUnit:1;	//0 if the limit is expressed in bytes or 1 if the limit is in pages
	u8  segmentBase_24_31;
} __attribute__ ((packed)); //__attribute__((packed)) so that the compiler doesn't change this structure and optimize it

struct gdtDescriptor GDT[GDTSIZE];//the global descriptor table,is an array of gdtDescriptors (segment entries)

/*!
 * the folowing are used to indicate the type of segment, we use afrendly names instead of using binary parameters
 * they are used as parameters of the function GDT_set_descriptor(.....)
 */
#define segmentType_CS  0xB	//the segment is a code segment
#define segmentType_DS  0x3	//to indicate that the segment being created is a data segment
#define kernelMode	0x0	//ring0, a segment used to contain kernel code
#define userMode	0x3	//ring3, used for ordinary applications that dont belong to the lernel
#define presentInMemory 0x1	//the segment is present in memory or is swapped to a backbone (a disk for exmple)
#define _32bitInstructions 0x1	//instructions in the segment are 32 bit instructions
#define _16bitInstructions 0x0
#define limitInBytes	0x0	//the limit of the segment is expressed in bytes (limit=0x100 means 0x100 bytes)  
#define limitInPages	0x1	//(limit=0x100 means 0x100 pages with each page can be 4k or 4M (on intel!)


/*!	
 * gdtPointer :  the gdt pointer is used to indicate the place of the gdt in memory
 */
typedef struct gdtPointer
{
	u16 limit;
	u32 base;
} __attribute__ ((packed));



u32 GDT_descriptors_number=0;	//the number of descriptors in the GDT
struct gdtPointer gdtr;


/*!	
 * GDT_init :  initialize the gdt table : insert the code and data segment and copy the gdt to a new place 
 */
 void GDT_init()
{
	//the first GDT is null
	GDT_set_descriptor(1,0x0,0xfffff,segmentType_CS,0x1,kernelMode,presentInMemory,_32bitInstructions,limitInPages);
	GDT_set_descriptor(2,0x0,0xfffff,segmentType_DS,0x1,kernelMode,presentInMemory,_32bitInstructions,limitInPages);
	
	//initialize the GDT pointer
	gdtr.base=GDT;
	gdtr.limit = sizeof(struct  gdtDescriptor)*GDTSIZE;	
	
	//make this GDT the system GDT by loading it to tne gdtr regiter
	GDT_install();
}


/*!	
 * GDT_set_descriptor :  set a GDT descriptor,
 * 	u32 descriptor	: witch descriptor to set (the descriptor 0 is not used),1 means the first descriptor
	u8  segmentType : 4;	//data segment or code segment or stack segment
	u8  segmentOrSystemCall :1;//to revise the name of this after you know what it does
	u8  Ring:2;	//ring0 is kernel segment and ring=3 for user mode segment,this used for protection
	u8  presentOrSwaped:1;	//to indicate if the segment is present in memory or it has been swaped to the HDD
	u8  segmentLimit_16_19:4;
	u8  NotUsed:2;		//this 2 bits feild is not used , so just put it to 0
	u8  instructionSize:1;	//instructionSize=1 for 32bit instructions
	u8  limitUnit:1;	//0 if the limit is expressed in bytes or 1 if the limit is in pages
	u32  segmentBase : adresse of the beginnig of the segment
  	u32 limit :size of the descriptor, if limitUnit=limitInBytes so this limit is expressed in byte not in pages
 * 
 */
void GDT_set_descriptor(u32 descriptor,u32 base,u32 limit,u8 segmentType,u8 segmentOrSystemCall,u8 ring,u8 presentOrSwaped, u8 instructionSize, u8 limitUnit)
{
	struct gdtDescriptor gd;
	
	//set gdt base
	gd.segmentBase_0_15=(base & 0xffff);
	gd.segmentBase_16_23=((base>>16) & 0xff);
	gd.segmentBase_24_31=((base>>24) & 0xff);
			
	//set gdt limit
	gd.segmentLimit_0_15= (limit & 0xffff);
	gd.segmentLimit_16_19=((limit>>16)  & 0xf);
	
	//other descriptor bits
	gd.segmentType=segmentType;
	gd.segmentOrSystemCall=segmentOrSystemCall;
	gd.Ring=ring;
	gd.presentOrSwaped=presentOrSwaped;
	gd.NotUsed=0;
	gd.instructionSize=instructionSize;
	gd.limitUnit=limitUnit;
	
	//add this gd descriptor to the GDT table
	GDT[descriptor]=gd;
	
}
		
		
		
/*!	
 * GDT_install :  load the new GDT to the gdtr register, that means 
 */		
void GDT_install()
{
	//we need assembly here ! to make the GDTR register points our new GDT 
	asm("lgdt (gdtr)");
}
		
		
/*!	
 * GDT_install :  load the new GDT to the gdtr register, that means 
 */		
void GDT_load_descriptor(u32 descriptor)
{
	//this function must be edited so that we can add a  code descriptor or a data descriptor
	//for exemple  GDT_load_descriptor_CS(2) this will load the second descriptor as a CS segment ie cs<--descriptor(2) 
}
		
		


				
