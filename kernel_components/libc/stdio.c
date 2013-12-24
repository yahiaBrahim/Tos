/*
 *	stdio.h : stadard Input/Output library
 *	version : 0.1
 *	19/07/2007
 *	this library can be optimized more, but since it's not a part of the MicroKernel it's not
 *	very important to optimize it.
*/

#ifndef _HEADER_STDIO_C
#define	_HEADER_STDIO_C

#include "../../kern/memory/memory.c"

#define args_list char *

#define _arg_stack_size(type) (((sizeof(type)-1)/sizeof(int)+1)*sizeof(int))

#define args_start(ap, fmt) do { ap = (char *)((unsigned int)&fmt + _arg_stack_size(&fmt)); } while (0)

#define args_end(ap)

#define args_next(ap, type) (((type *)(ap+=_arg_stack_size(type)))[-1])

static char buf[1024] = {-1};
static int ptr = -1;


/* valid base: 2, 8, 10 */

static void

parse_num(unsigned int value, unsigned int base) {

        unsigned int n = value / base;

        int r = value % base;

        if (r < 0) {

                r += base;

                --n;

        }

        if (value >= base)

                parse_num(n, base);

        buf[ptr++] = "0123456789"[r];

}

static void
parse_hex(unsigned int value) {

        int i = 8;

        while (i-- > 0) {

                buf[ptr++] = "0123456789abcdef"[(value>>(i*4))&0xf];

        }
}





#define	MEM_VIDEO 0XB8000			// the beginning of video memory
#define SCREEN_LIM 0xB8FA0			// do the size of the video memory = 0xFA0
#define MEM_VIDEO_SIZE 0xFA0			// size of video memory
#define BACK_MEM_VIDEO 0xB7060			// Back video memory zone:used to store lines that are scrolled (by the function scroll), it has a size of 0xFA0 
#define LINE_SIZE (2 * LINES_COUNT)		//the size of a line

char LINES_COUNT=80;				// number of lines in the shell (window!)
char COLUMNS_COUNT=25;				
char CAR_ATTR = 0x07; 				// attribut(color of the caracter)(black & white)
char OLD_CAR_ATTR = 0x07;			//to save CAR_ATTR whan it changes
int CUR_X = 0; 					//current cursor postion (Psition for X )
int CUR_Y = 10;
char * BACK_MEM_VIDEO_PTR = BACK_MEM_VIDEO;	//a pointer on the BACK_MEM_VIDEO zone: points the last line that came from the scroll function. i.e the last saved line.

#define TAB_SPACE 0x7				//tab space
void memcopy(void * adr1, void * adr2, int n);
void putchar(unsigned char c);
void print(char *str);
void gotoxy(const char x, const char y);

/*! 
 * scrollup screen(up),copy the first line of the MEM_VIDEO (screen) to the BACK_MEM_VIDEO 
 * (a zone to store lines that are scrolled up
 */
void scroll (unsigned int n) 
{
	int i,cx,cy;
	if (n > 0)				//scroll up
	{
		memcopy(MEM_VIDEO , BACK_MEM_VIDEO_PTR, LINE_SIZE*n);
		/*! copy the first line of video memory to the back video memory 
		(the place where we store the lines the we clean by the scroll up function)
		we have to soluutions to manage the BACK_MEM_VIDEO : to put the last line
		scrolled up in the bottom (the end) of the BACK_MEM_VIDEO and the rest of 
		this zone is also scrolled up*/
		memcopy(MEM_VIDEO + LINE_SIZE*n , MEM_VIDEO, MEM_VIDEO_SIZE - LINE_SIZE*n);
		/* copy the rest of the VIDEO_MEM*/
		
	}
	else
	{
		//I have a small problem here
		//memcopy(MEM_VIDEO, MEM_VIDEO+LINE_SIZE*(-n), LINE_SIZE*(-n));
		//memcopy(BACK_MEM_VIDEO_PTR + LINE_SIZE*n , MEM_VIDEO , LINE_SIZE*(-n));
	}
}

/*!
  Deletes a line from the screen
 Input: line number
*/
void delline(int y)
{	unsigned char * MEM ;
	int i;
	for(i=0;i<LINES_COUNT;i++)
	{
		MEM=(unsigned char*)( MEM_VIDEO + i * 2 + y * 160);
		*MEM=' ';//On efface le caractere 
		*(MEM+1)=CAR_ATTR;
	}	
}
/*!
Writes a character (an unsigned char) specified by the argument char to the screen.
*/
void putchar(unsigned char c)
{
	unsigned char * MEM ;
	
	switch(c)
	{
        //si c'est un retour à la ligne 
	case '\n' :     if(CUR_Y < COLUMNS_COUNT -1) CUR_Y++;
	else {scroll(1);
		delline(CUR_Y);
	}
			CUR_X=0;
			break;
        
        //Si c'est une tabulation
	case '\t' :     CUR_X += TAB_SPACE;
			if(CUR_X >= LINES_COUNT)		//there is a space in this line
			{
			if(CUR_Y < COLUMNS_COUNT -1) CUR_Y++;
			else {scroll(1);
				delline(CUR_Y);
			}
			CUR_X=CUR_X % LINES_COUNT;	
			}
		  	break;

        //Si c'est le caractere de supression
        case '\b':    CUR_X--;
                       if(CUR_X<0)
		       {       if(CUR_Y>0) //if we are not in top line
		       	      {
			       CUR_X=LINES_COUNT-1;
			       CUR_Y--;
		       	      }
			      else CUR_X=0;
				      
		       };
                       MEM=(unsigned char*)( MEM_VIDEO + CUR_X * 2 + CUR_Y * 160);
		       *MEM=' ';//On efface le caractere 
		       *(MEM+1)=CAR_ATTR;
		       break;
		       
	default   :				//not <ENTER>
		  {
			//calculate the postion where to put the caracter in the video memory
			MEM= (unsigned char *) ( MEM_VIDEO + CUR_X * 2 + CUR_Y * 160);
			//write   c    on the screen
			*MEM = c;
			*(MEM + 1) = CAR_ATTR;
			//prepare for the next char
			CUR_X++;
			
			if(CUR_X >= LINES_COUNT)		//there is a space in this line
			{
			  if(CUR_Y < COLUMNS_COUNT) CUR_Y++;
			  else {scroll(1);
				  delline(CUR_Y);
			  }
			  CUR_X=0;	
			}
		  }
	}
}


/*!
Writes a string (that ends with '\0') to the screen, it returns to line if necessary.
*/
/*void print(char * str)
{
	register char * s = str;
	while(*s)			
	{
		putchar(*s);
		s++;
	}
}*/

void printf(const char *fmt, ...)
{
       int i = 0;

        char *s;

        args_list args;

        args_start(args, fmt);

 

        ptr = 0;

 

        for (; fmt[i]; ++i) {

                if ((fmt[i]!='%') && (fmt[i]!='\\')) {

                        buf[ptr++] = fmt[i];

                        continue;

                } else if (fmt[i] == '\\') {

                        /* \a \b \t \n \v \f \r \\ */

                        switch (fmt[++i]) {

                        case 'a': buf[ptr++] = '\a'; break;

                        case 'b': buf[ptr++] = '\b'; break;

                        case 't': buf[ptr++] = '\t'; break;

                        case 'n': buf[ptr++] = '\n'; break;

                        case 'r': buf[ptr++] = '\r'; break;

                        case '\\':buf[ptr++] = '\\'; break;

                        }

                        continue;

                }

/* fmt[i] == '%' */

                switch (fmt[++i]) {

                case 's':

                        s = (char *)args_next(args, char *);

                        while (*s)

                                buf[ptr++] = *s++;

                        break;

                case 'c':

                        /* why is int?? */

                        buf[ptr++] = (char)args_next(args, int);

                        break;

                case 'x':

                        parse_hex((unsigned long)args_next(args, unsigned long));

                        break;

                case 'd':

                        parse_num((unsigned long)args_next(args, unsigned long), 10);

                        break;

                case '%':

                        buf[ptr++] = '%';

                        break;

                default:

                        buf[ptr++] = fmt[i];

                        break;

                }

        }

        buf[ptr] = '\0';

args_end(args);

        for (i=0; i<ptr; ++i)

                putchar(buf[i]);
}


/*!
gotoxy : changes the position of the cursor
*/
void gotoxy(const char x, const char y)
{
	if (x<LINES_COUNT  &&  y<COLUMNS_COUNT)
	{
		CUR_X=x;
		CUR_Y=y;
	}
}

void setTextColor(char color)
{				
	OLD_CAR_ATTR = CAR_ATTR ;
	CAR_ATTR     = color;
}



/*! 
 * clrscr : clear screen and returns cursor to (0,0)
 */
void clrscr()
{
	int i;
	
	gotoxy(0,0);				
	for (i=0; i<LINES_COUNT*COLUMNS_COUNT; i++)
	{
		putchar(' ');			//writes a blanc : ' '
	}
	gotoxy(0,0);
}



unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

#endif
