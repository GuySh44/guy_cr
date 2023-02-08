#include <pthread.h> /* pthread_create pthread_attr_setdetachstate pthread_attr_init */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

/*
Reviewer: Yarin
*/

/*
time stats:
real	0m11.283s
user	0m0.488s
sys		0m1.913s


*/

static int array[100000] = {0};

void *SetIndex(void *i)
{
	array[((long)i)] = ((long)i);
	return array + ((long)i);
}


int main()
{
	pthread_t id;
	int *ptr = NULL;
	size_t i = 0;
	
	pthread_attr_t attr = {0};
	
	if(pthread_attr_init(&attr))
	{
		return 1;
	}
	
	if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
	{
		return 1;
	}
	
	for(; i < 100000; ++i)
	{
		while(0 != pthread_create(&id, &attr, SetIndex, (void *)i));
	}

	
	sleep(10);
	
	i = 0;
	
	for(; i < 100000; ++i)
	{
		if(array[i] != (int)i)
		{
			printf("mission failed\n");
			return 1;
			/*printf("%lu Not equal\n", i);*/
		}
	}
	
	printf("we gucci\n");
	
	return 0;
}
