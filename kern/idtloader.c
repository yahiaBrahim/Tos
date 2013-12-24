/*!
 * summary : 
 Here we will load the IDT (Interuption Description Table) which contain the 
 interputions handlers adresses.

 There are two type of Int , the matrial and the software one.The software Ints are used to
 do some services or to handel error and so on. some times we can consider system calls as a third type of interrupts but we don't use this in Tos.
 and the matial ones are Int used to communicate with hardware , all the hardware Int comme 
 throw the µControler 8259 . There are two µcontrollers one master and the other is a slave , each one can hadel up to 8 IRQs(hardware Ints) ,so the master handels IRQ from 0-7 and the slave hadels the rest (8-15).
 
 A said befor the IDT pints each Int routine .In our case we have organised the IDT in this way
 (the general way)
 -The first 32 entries are used for Software Ints .
 -The next 16 entries are used to handel to 8258 Ints.

The 8259 is programmed to fire Int to the entries 0-15 , in this case those 16 entries are used
by the CUP ints ,so we have to re-map the Ints to be handled by the entries 20-2F.



 The IDT will be :
  ;----------------------------;\
  ;       IDT[0]               ; \
  ;----------------------------;  \
  ;                            ;   \
  ;                            ;    \---- Interuptions du CPU
  ;                            ;   /
  ;----------------------------;  / 
  ;       IDT[31]              ; /
  ;----------------------------;/
  ;----------------------------;\
  ;       IDT[32]              ; \
  ;----------------------------;  \
  ;                            ;   \
  ;                            ;    \---- IRQs
  ;                            ;   /
  ;----------------------------;  / 
  ;       IDT[47]              ; /
  ;----------------------------;/
  ;----------------------------;\
  ;                            ; \
  ;                            ;  \
  ;                            ;   \
  ;                            ;    \---- Appels Systemes
  ;                            ;   /
  ;                            ;  / 
  ;                            ; /
  ;----------------------------;/;
  
 * version : 0.1
 * last modification : 24/08/2007
 * authors : Nadhir
 * emails  : altctrlsup@yahoo.com*/
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */



#include"idtloader.h"



struct IDTSegDesc IDT[256];//We use 256 Int
struct IDTP  idtptr; //IDT pointer

/*!
  Fills the the entry Num with the informations about the Int handler
Entries:
  Num :the place were the new Int handler will be put.
  Base :The base adress of the routine (Segment:Offset)
  Flag :The Flag
*/
void AddInt(int Num,unsigned long Base,unsigned dis,unsigned char Flag)
{
 IDT[Num].BaseLow = Base & 0xFFFF;
 IDT[Num].BaseHi  = (Base>>16) & 0xFFFF;
 IDT[Num].Flag=Flag;
 IDT[Num].discrpteur=dis;
 //IDT[Num].Azero=0; facultatif car on l'a deja fait dans l'initialisation de la idt
};


/*!
 Intialise all the IDT entries: 
 -Fill all the entries with 0x00.
 -Intialise the IDT pointer
 -Setup the CPU and IRQ handlers
 - remap the 8259.
*/
void InitIDT(void)
{
 //Initlise all the entries to 0x00
 int i;
 for(i=0;i<256;i++)
 {
  IDT[i].BaseLow =0;
  IDT[i].BaseHi  =0;
  IDT[i].Flag=0;
  IDT[i].discrpteur=0;
  IDT[i].Azero=0;
 };

 //Initialise the IDT pointer
 idtptr.Limit =256*8 -1;
 idtptr.Base = &IDT;

 //Add the routines pointers
 InitCPUInt();
 InitIRQs();
 //And then remap the 8259
 MapIRQs(32);
}



/*!
 Setup the CPU handlers
*/
void InitCPUInt(void)
{
	
 AddInt(0,(unsigned)DEVZERO,0x8,0x8E);
 AddInt(1,(unsigned)DEBUGISR,0x8,0x8E);
 AddInt(2,(unsigned)NONMASKABLEINT,0x8,0x8E);
 AddInt(3,(unsigned)BRPTSISR,0x8,0x8E);
 AddInt(4,(unsigned)INTODETOV,0x8,0x8E);
 AddInt(5,(unsigned)OUTBOUNDS,0x8,0x8E);
 AddInt(6,(unsigned)INVALIDOP,0x8,0x8E);
 AddInt(7,(unsigned)NOCOPP,0x8,0x8E);
 AddInt(8,(unsigned)DOUBLEF,0x8,0x8E);
 AddInt(9,(unsigned)COSEGOV,0x8,0x8E);
 AddInt(10,(unsigned)BADTSS,0x8,0x8E);
 AddInt(11,(unsigned)SEGNOTP,0x8,0x8E);
 AddInt(12,(unsigned)STKFAULT,0x8,0x8E);
 AddInt(13,(unsigned)GPROFAULT,0x8,0x8E);
 AddInt(15,(unsigned)PAGEFAULT,0x8,0x8E);
 AddInt(16,(unsigned)UNKOWNINT,0x8,0x8E);
 AddInt(17,(unsigned)COPFAULT,0x8,0x8E);
 AddInt(18,(unsigned)ALIGNCHECK,0x8,0x8E);
 AddInt(19,(unsigned)MCHECK,0x8,0x8E);
};




/*!
Setup the IRQ handlers
*/
void InitIRQs(void)
{
	AddInt(32,(unsigned) IrqTimer,0x8,0x8E);
	AddInt(33,(unsigned) IrqKeyboard,0x8,0x8E);
	AddInt(34,(unsigned) IrqCascade,0x8,0x8E);
	AddInt(35,(unsigned) IrqCOM2_4,0x8,0x8E);
	AddInt(36,(unsigned) IrqCOM1_3,0x8,0x8E);
	AddInt(37,(unsigned) IrqLpt,0x8,0x8E);
	AddInt(38,(unsigned) IrqFloppy,0x8,0x8E);
	AddInt(39,(unsigned) IrqFree7,0x8,0x8E);
	AddInt(40,(unsigned) IrqClock,0x8,0x8E);
	AddInt(40,(unsigned) IrqFree9,0x8,0x8E);
	AddInt(42,(unsigned) IrqFree10,0x8,0x8E);
	AddInt(43,(unsigned) IrqFree11,0x8,0x8E);
	AddInt(44,(unsigned) IrqPS2Mouse,0x8,0x8E);
	AddInt(45,(unsigned) IrqCoproc,0x8,0x8E);
	AddInt(46,(unsigned) IrqIDE_1,0x8,0x8E);
	AddInt(47,(unsigned) IrqIDE_2,0x8,0x8E);
};



/*!
 Used to remap the 8259 , starting from the adress Addr
*/
void MapIRQs(unsigned char Addr)
{
	outportb(0x20, 0x11); /* ICW1 */
	outportb(0xA0, 0x11);
    
	outportb(0x21, Addr); /* ICW2: route IRQs 0...7 to INTs Addr...Addr+7 */
	outportb(0xA1, Addr+8); /* ...IRQs 8...15 to INTs Addr+8 ... Addr+15 */

	outportb(0x21, 0x04); /* ICW3 */
	outportb(0xA1, 0x02);

	outportb(0x21, 0x01); /* ICW4 */
	outportb(0xA1, 0x01);
};
