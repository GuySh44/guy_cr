#include <dlfcn.h>
#include <stdio.h>

#include "memory_map.h"

int main()
{
	typedef void (*fp)();
	fp foo;
	void *foo_lib;
	char* error;
	
	
	
	foo_lib = dlopen("./libmydynamic.so", RTLD_NOW);
	
	if (!foo_lib) 
	{
    	printf("Error loading library: %s\n", dlerror());
    	return 1;
  	}
  	
  	dlerror();
	
	*((void**)(&foo)) = dlsym(foo_lib, "Foo");
	
	error = dlerror();
	
  	if (error) 
  	{
    	printf("Error loading symbol: %s\n", error);
    	return 1;
  	}
  	
	foo();
	
	dlclose(foo_lib);
	return 0;
}
