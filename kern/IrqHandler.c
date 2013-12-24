/*!
 * summary : 
 * version : 0.1
 * last modification : 24/08/2007
 * authors : Nadhir
 * emails  : 
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */



void NotyetDone(void)
{
  printf("Other IRQ\n");
  outportb(0xA0,0x20);
  outportb(0x20,0x20);
}



void TimeHandler()
{
  outportb(0xA0,0x20);
  outportb(0x20,0x20);
}
