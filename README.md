# LowLevelDebugC

how to use

* Add the debug.h to your proyect
```c
#include"debug.h"
```

*replace any call to malloc, calloc, realloc and free to debug_malloc, 


*at the beggining of your main funtion  call to debug_init funtion, this is before any call to the custom funtions
```c
debug_init();
```

*wherever you want to know how much memory are you reserving with alloc funtions call the debug_status funtion

```c
debug_status();
```

Example:


```c
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

```

compile and execute

output:

```
Current memory Allocated: 2097152 bytes
Current total chunks used : 2
Pointer not found 0x7f8f5a4c0010
May be you missing change some malloc, calloc realloc?
Or pointer previously release```



