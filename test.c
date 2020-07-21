#include<stdlib.h>
#include<stdio.h>

#include"debug.h"


int main()	{
	char *memoria;
	debug_init();

	memoria = debug_malloc(1024*1024);
	
	/*
		do something!
	*/
	debug_status();
	return 0;
}