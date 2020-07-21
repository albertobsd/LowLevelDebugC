#pragma once
#include<pthread.h> 
#include<string.h>
#include<stdlib.h>

#define DEBUG_ITEMS_MAX 0
#define DEBUG_ITEMS 1
#define DEBUG_INDEX 2
#define DEBUG_MEMORY 3

pthread_mutex_t debug_lock; 

char *debug_malloc(int length);
void debug_free(char *ptr);

void debug_optimizar();
void debug_add(char *ptr,int length);
void debug_remove(char *ptr);
void debug_status();


char **debug_ptr = NULL;
int *debug_ptr_sizes = NULL;
int *debug_valores = NULL;

char *debug_malloc(int length)	{
	char *ptr = NULL;
	ptr = (char*) malloc(length);
	if(ptr)	{
		debug_add(ptr,length);
	}
	else	{
		perror("malloc");
	}
	return ptr;
}

void debug_free(char *ptr)	{
	if(ptr)	{
		debug_remove(ptr);
		free(ptr);
	}
}

void debug_add(char *ptr,int length)	{
	pthread_mutex_lock(&debug_lock);
	if(debug_valores[DEBUG_INDEX] >= debug_valores[DEBUG_ITEMS_MAX])	{
		debug_valores[DEBUG_ITEMS_MAX]*=2;
		debug_ptr = realloc(debug_ptr,debug_valores[DEBUG_ITEMS_MAX]*sizeof(char*));
		debug_ptr_sizes = realloc(debug_ptr_sizes,debug_valores[DEBUG_ITEMS_MAX]*sizeof(int));
	}
	debug_ptr[debug_valores[DEBUG_INDEX]] = ptr;
	debug_ptr_sizes[debug_valores[DEBUG_INDEX]] = length;
	debug_valores[DEBUG_MEMORY]+=length;
	debug_valores[DEBUG_ITEMS]++;
	if(debug_valores[DEBUG_INDEX] % 20 == 0)	{
		debug_optimizar();
	}
	debug_valores[DEBUG_INDEX]++;
	pthread_mutex_unlock(&debug_lock);
}

void debug_remove(char *ptr)	{
	int i = 0;
	int encontrado = 0;
	pthread_mutex_lock(&debug_lock);
	while( !encontrado && i < debug_valores[DEBUG_INDEX] )	{
		if(ptr == debug_ptr[i])	{
			encontrado = 1;
			debug_ptr[i] = NULL;
			debug_valores[DEBUG_MEMORY] -= debug_ptr_sizes[i];
			debug_ptr_sizes[i] = 0;
			debug_valores[DEBUG_ITEMS]--;
		}
		i++;
	}
	if(encontrado == 0)	{
		printf("Pointer not found %p ptr - you missing change some malloc, calloc realloc?\n",ptr	);
	}
	pthread_mutex_unlock(&debug_lock);
}

void debug_optimizar()	{
	int i = 0,aux,items;
	while(i < debug_valores[DEBUG_INDEX] ){
		if(debug_ptr[i] == NULL)	{
			items = debug_valores[DEBUG_INDEX] - i;
			memcpy(&debug_ptr[i],&debug_ptr[i+1],items * sizeof(char*));
			memcpy(&debug_ptr_sizes[i],&debug_ptr_sizes[i+1],items * sizeof(int));
			debug_ptr[debug_valores[DEBUG_INDEX]] = NULL;
			debug_ptr_sizes[debug_valores[DEBUG_INDEX]] = 0;
			i--;			
			debug_valores[DEBUG_INDEX]--;
		}
		i++;
	}
}

void debug_init()	{
	if(debug_ptr == NULL)	{
		debug_valores = (int*) calloc(4,sizeof(int));
		debug_valores[DEBUG_ITEMS_MAX] = 2;
		debug_ptr = (char**)calloc(debug_valores[DEBUG_ITEMS_MAX],sizeof(char*));
		debug_ptr_sizes = (int*)calloc(debug_valores[DEBUG_ITEMS_MAX],sizeof(char*));
	}
	if(pthread_mutex_init(&debug_lock, NULL)  != 0)	{
		perror("pthread_mutex_init");
		exit(1);
	}
}

void debug_status()	{
	pthread_mutex_lock(&debug_lock);
	printf("Current memory Allocated: %i bytes\n",debug_valores[DEBUG_MEMORY]);
	printf("Current total chunks used : %i\n",debug_valores[DEBUG_ITEMS]);
	pthread_mutex_unlock(&debug_lock);
}