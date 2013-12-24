/*
 * summary : 
 
 Les discripteur de la IDT sont 64 bits de taille.
   un discripteur de segment de la IDT fournis plusieurs information utils comme l'@ de
   la routine responsable du traitement de l'int, le niveau du privilege de cette routine

   un discripteur à la structure suivante:
    ________________________________
   |         BASE(16..30)           |
    --------------------------------
   |P|  DPL | 0X0E  |0 0 0 0 0 0 0 0|
    --------------------------------
   |           BASE(0..15)	        |
    -------------------------------- <--- @
 
P : Bit de presence
DPL: Descriptor Privilege Level 


 * version : 0.1
 * last modification : 24/08/2007
 * authors : Nadhir
 * emails  : 
 * -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */

/* 
*/ 
struct IDTSegDesc
{
  unsigned short BaseLow; //16 bits du poid faible de l'@ de la routine
  unsigned short discrpteur; // @ du segment de la routine
  unsigned char  Azero;//cette entrée est toujour à zero
  unsigned char  Flag;
  unsigned short BaseHi;//16 bits du point fort de l'@ de la routine
}__attribute__((packed));

struct IDTP
{
 unsigned short Limit;
 unsigned int Base;
}__attribute__((packed));

void AddInt(int Num,unsigned long Base,unsigned dis,unsigned char Flag);
void InitIDT(void);
void InitCPUInt(void);
void InitIRQs(void);
void MapIRQs(unsigned char Addr);

extern void  DEVZERO(void);
extern void  DEBUGISR(void);
extern void  NONMASKABLEINT(void);
extern void  BRPTSISR(void);
extern void  INTODETOV(void);
extern void  OUTBOUNDS(void);
extern void  INVALIDOP(void);
extern void  NOCOPP(void);
extern void  DOUBLEF(void);
extern void  COSEGOV(void);
extern void  BADTSS(void);
extern void  SEGNOTP(void);
extern void  STKFAULT(void);
extern void  GPROFAULT(void);
extern void  PAGEFAULT(void);
extern void  UNKOWNINT(void);
extern void  COPFAULT(void);
extern void  ALIGNCHECK(void);
extern void  MCHECK(void);
extern void  RESERVED1(void);
extern void  RESERVED2(void);
extern void  RESERVED3(void);
extern void  RESERVED4(void);
extern void  RESERVED5(void);
extern void  RESERVED6(void);
extern void  RESERVED7(void);
extern void  RESERVED8(void);
extern void  RESERVED9(void);
extern void  RESERVED10(void);
extern void  RESERVED11(void);
extern void  RESERVED12(void);
extern void  RESERVED13(void);

//Les IRQs
extern void IrqTimer(void);
extern void IrqKeyboard(void);
extern void IrqCascade(void);
extern void IrqCOM2_4(void);
extern void IrqCOM1_3(void);
extern void IrqLpt(void);
extern void IrqFloppy(void);
extern void IrqFree7(void);
extern void IrqClock(void);
extern void IrqFree9(void);
extern void IrqFree10(void);
extern void IrqFree11(void);
extern void IrqPS2Mouse(void);
extern void IrqCoproc(void);
extern void IrqIDE_1(void);
extern void IrqIDE_2(void);
