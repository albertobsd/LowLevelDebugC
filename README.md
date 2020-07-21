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
	char *memoria;
	debug_init();
	memoria = debug_malloc(1024*1024);
	/*
		do something!
	*/
	debug_status();
	return 0;
}
```

compile and execute

output:

```
Current memory Allocated: 1048576
Current total chunks used : 1

```



