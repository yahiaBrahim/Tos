/*!
 * summary : input / output
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

struct iobuff
{
   char Buff[8];
   int ptr;
   int in;
}kbbuff;



void add(char c)
{
	if(kbbuff.in<8)//Si le buffer n'est pas vide
	{
		kbbuff.Buff[(kbbuff.ptr+kbbuff.in)%8]=c;
		kbbuff.in++;
	}		
}



char getkey(void)
{
	char c;
	if(kbbuff.in>0)
	{
		c= kbbuff.Buff[kbbuff.ptr];
		kbbuff.in--;
		kbbuff.ptr=(kbbuff.ptr+1)%8;
		return c;
	}
	else
	{
		return 0x0;
	}
}



void scan(char * cmd)
{
	
	char t[2]={0,0};
	int i=0;
	//tanqu'on a pas encore tapper ENTRER alors on continue à lire
	t[0]=getkey();	
	while(t[0]!='\n')
	{
		if(t[0]!=0x0)
		{
			if(t!='\b')
			{
			 cmd[i]=t[0];
			 i++;
			}
			else i--;
			if(i<255)printf(t);
		}
		t[0]=getkey();
	}
	if(i<255)cmd[i]=0x0;
	else cmd[255]=0x0;
	printf('\n');
}
