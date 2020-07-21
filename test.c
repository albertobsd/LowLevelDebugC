#include<stdlib.h>
#include<stdio.h>

#include"debug.h"


int main()	{
	char *m1,*m2,*m3;
	debug_init();
	m1 = (char*)debug_malloc(1024*1024);
	m2 = (char*)debug_calloc(1024*512,1);
	m3 = (char*)debug_realloc((void*)m2,1024*1024);
	/*
		do something!
	*/
	debug_status();
	debug_free(m2);	//m2 was reallocated this should show error unless  m2 == m3 was true
	return 0;
}