/*!
 * summary : linked lists 
 * version : 0.1
 * last modification : 27/12/2007
 * authors : Baghdadi Mohamed Riyadh
 * emails  : Baghdadi13@gmail.com 				*/
 /* -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS) which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */

//#include "../../kern/memory/memory.c"
//#include "../../libc/string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define NODE_DATA_SIZE 32

typedef struct NODE * ptr; 	//pointer on a node

typedef struct NODE
{  	
                 void * object;
                 ptr next;
} node;


ptr node_alloc()
{
	return (ptr)malloc(sizeof(node));
}

void node_free(ptr p)
{
	//not yes implemented
	//free(p);
}

void set_value(ptr p, void * value)
{
	p->object= value;
}

void set_next(ptr p,ptr q)
{
	p->next=q;
}

char * value(ptr p)
{
	return  p->object;
}

ptr list_next(ptr p)
{
	return p->next;
}

ptr list_add(ptr * p, void * value ) 
{
	ptr n = (ptr)malloc(sizeof(node));
	if (n == NULL)
		return NULL;
	set_next(*p,n);                                                                            
	set_value(n,value);
	set_next(n,NULL);
	
	return n;
}

void list_print(ptr p)
{
      int i=0;

      while( p )
      {
            printf("node=%d, value=%s\n",i, (char *) p->object);
            i++;
            p=list_next(p);
      }     
      printf("NULL\n");
}
 
/* for tests only
int main()
{
      	ptr head,p;

	printf("start");
        
        head=node_alloc();
	p=list_add(&head,"abb");
	p=list_add(&p,"c");
        list_print(head);
	
	
}
*/
