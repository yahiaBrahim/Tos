#include <stdlib.h>
#include "stdio.h"
#include "../libc/string.h"


#define BUFFER_SIZE 512
#define COMMAND_CHAR ':'		//a special character that preceeds any command
#define false 0
#define true 1
#define EXIT_CHAR 'q'

char buffer[BUFFER_SIZE];	//buffer


int SaveFile()
{
	char  fileName[20];
	char * ff="ffffffff";
	FILE * F;
	
	printf("file name :");
	//read the file name
	strcpy(fileName,readline());
	strcpy(ff,fileName);
	F= fopen(ff,"wb");
	fprintf(F,buffer,sizeof(BUFFER_SIZE));
	fclose(F);
}



int OpenFile()
{
	printf("opening file ...");
}




int Command(char cmd)
{

switch(cmd) 
{
		case 'S' ://save file
		case 's' :SaveFile();
			break;
				
		case 'o' ://open file
		case 'O' :OpenFile();
			break;
			
		case 'q' ://exit
		case 'Q' :return true;		//the main function we will get exit = true
			break;	
	}
	
}




int main()
{
	
	int i=0;			//used to write in the buffer
	char car;			//read characters that will be writen to the byffer
	char cmd;			//a character that represents a command
	int exit=false;			//don't exit until we get the commang quit 'q'
	
		car=getchar();
		while((!exit) && (car != EXIT_CHAR))
		{	
			if(car != COMMAND_CHAR)
			{
				buffer[i]=car;
				i++;
				//print car on the screen
			}
			else
			{
				printf("command To be executed ...\n");
				cmd=getchar();
				exit = Command(cmd);	//deal with this command passed as character
			}
			car=getchar();
		}
}
