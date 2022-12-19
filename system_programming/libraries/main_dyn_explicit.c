#include <dlfcn.h>
#include <stdio.h>

int main()
{
	typedef void (*fp)(int);
	void *dyn = dlopen("./libdyn.so", RTLD_NOW);
	fp my_foo;
	char* error;
	
	if (!dyn) 
	{
    	printf("Error loading library: %s\n", dlerror());
    	return 1;
  	}
  	
  	dlerror();
	
	*((void**)(&my_foo)) = dlsym(dyn, "Foo");
	
	error = dlerror();
	
  	if (error) 
  	{
    	printf("Error loading symbol: %s\n", error);
    	return 1;
  	}
  	
	my_foo(2);
	dlclose(dyn);
	return 0;
}
