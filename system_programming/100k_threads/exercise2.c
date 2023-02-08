#include <pthread.h> /* pthread_create */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <errno.h>

/*
Reviewer: Yarin
*/

/*
time stats:
real	0m12.415s
user	0m0.657s
sys		0m2.774s

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
	size_t i = 0;
	
	int *ptr = NULL;
	
	
	for(; i < 100000; ++i)
	{
		while(0 != pthread_create(&id, NULL, SetIndex, (void *)i))
		{
			perror(NULL);
			pthread_join(id, (void**)&ptr);
		}
		
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
