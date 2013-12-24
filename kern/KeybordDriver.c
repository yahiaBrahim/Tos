/*!
 * summary : The keybord IRQ handler , it uses the Set1 scancodes.
 * version : 0.1
 * last modification : 24/08/2007
 * authors : Nadhir
 * emails  :altctrlsup [at] yahoo.com 				*/
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */



#include "io.h"

#define SPECIAL 0x00
#define ESCAPE  0x01
#define BKSPACE '\b'
#define TAB	'\t'
#define ENTRER  '\n'
#define CTRL	0x00
#define LSHIFT  0x2A
#define RSHIFT  0x36
#define PRNTSCR 0x00
#define ALT     0x00
#define CAPS	0x00
#define F1	0x00
#define F2	0x00
#define F3	0x00 
#define F4	0x00
#define F5	0x00
#define F6	0x00
#define F7	0x00
#define F8	0x00
#define F9	0x00
#define F10	0x00
#define NUM     0x00
#define SCRL    0x00
#define F11	0x00
#define F12	0x00

int up=0;//Indicates wheter the Shift key is Down(1) or Up(0)

/*It's not a real English key there are permutation of next keys :
 - A and Q.
 - m and ;
 - Z and W
 - M and :
*/
char charTable[]={SPECIAL,ESCAPE,'1','2','3','4','5','6','7','8','9','0','-','=',BKSPACE, 
TAB,'a','z','e','r','t','y','u','i','o','p','[',']',ENTRER,CTRL,
'q','s','d','f','g','h','j','k','l','m','\'','\\',LSHIFT,
'<','w','x','c','v','b','n',';',',','.','/',RSHIFT,PRNTSCR,ALT,
' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUM,SCRL,F11,F12,SPECIAL,
SPECIAL,SPECIAL 
};

char ShiftcharTable[]={SPECIAL, ESCAPE,'!','@','#','$','%','^','&','*','(',')','_','+',BKSPACE, 
TAB, 'A','Z','E','R','T','Y','U','I','O','P','{','}',ENTRER,CTRL,
'Q','S','D','F','G','H','J','K','L','M','"',LSHIFT,'|',
'>','W','X','C','V','B','N',':','<','>','?',RSHIFT,PRNTSCR,ALT,
' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUM,SCRL,F11,F12,SPECIAL,
SPECIAL,SPECIAL,    
};

char non_printable[22]={SPECIAL,ESCAPE,CTRL,PRNTSCR,ALT,
CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUM,SCRL,F11,F12};

/*!
 Converts an integer value to a Hex repesentation
 used in general for debugging purpose
*/
char * Hexconvert(int val)
{
  char tab[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  char v[5]={0x30,0x30,0x30,0x30,0x0};
  int cpt=0;
  
  do
  {
	  v[cpt]=tab[val%16];
	  cpt--;
	  val =val /16;
  }while(val !=0 & cpt >=0);
  return v;
}

/*!
 The keybord IRQ handler
*/
void KbHandler(void)
{
	char key;
	unsigned char cmd; 
	char ascii;
	int i;  
	key =inportb(0x60);//read the pressed key

	if(key<sizeof(charTable))//If key down
	{
		//if shift
		if((key==LSHIFT)|| (key==RSHIFT)) up=1;
		else
		{
			if(up)ascii=ShiftcharTable[key];
			else ascii=charTable[key];
			//check if it's a printable character
			int i=1,j;
			for(j=0;j<sizeof(non_printable);j++)
				if(ascii==non_printable[j]){
					i=0;
					break;
				};
				
			if(i)//If printable add to the keybord buffer
			{  
				add(ascii);
			}
		}
	}
	else
	{
		i=(int)key;
		i &=0x000000FF;//Make sur that convertion is all right
		//Check if the shift key is released
		if((i==RSHIFT+0x80)||(i==LSHIFT+0x80)) up=0;
	}
	

	cmd=inportb(0x61);
	outportb(0x61,cmd | 0x80);  //Deactivate the keybord
	outportb(0x61,cmd); //Restore the previous state
	outportb(0xA0,0x20);//EOI(End Of Interupt) to the Slave
	outportb(0x20,0x20);//EOI to the master
}
