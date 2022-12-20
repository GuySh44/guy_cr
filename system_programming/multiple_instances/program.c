#include <dlfcn.h>
#include <stdio.h>
#include "mystatic.h"

int main()
{
	typedef void (*fp)();
	fp foo1, foo2;
	void *foo1_lib, *foo2_lib;
	char* error;
	
	
	
	PrintGlobalVariableAddress();
	
	
	
	foo1_lib = dlopen("./libmydynamic1.so", RTLD_NOW);
	
	if (!foo1_lib) 
	{
    	printf("Error loading library: %s\n", dlerror());
    	return 1;
  	}
  	
  	dlerror();
	
	*((void**)(&foo1)) = dlsym(foo1_lib, "Foo");
	
	error = dlerror();
	
  	if (error) 
  	{
    	printf("Error loading symbol: %s\n", error);
    	return 1;
  	}
  	
	foo1();
	
	
	
	
	foo2_lib = dlopen("./libmydynamic2.so", RTLD_NOW);
	
	if (!foo2_lib) 
	{
    	printf("Error loading library: %s\n", dlerror());
    	return 1;
  	}
  	
  	dlerror();
	
	*((void**)(&foo2)) = dlsym(foo2_lib, "Foo2");
	
	error = dlerror();
	
  	if (error) 
  	{
    	printf("Error loading symbol: %s\n", error);
    	return 1;
  	}
  	
	foo2();
	
	dlclose(foo1_lib);
	
	dlclose(foo2_lib);
	return 0;
}
