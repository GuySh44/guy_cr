#include <stdio.h>
#include <unistd.h> /* sleep */


int main()
{
	int i = 5;
	for(; i > 0; --i)
	{
		printf("%d\n", i);
		sleep(1);
	}
	
	return 0;	
}
