#include <pthread.h> /* pthread_create */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

/*
Reviewer: Yarin
*/


/*
time stats:
non-opt:
real	0m10.997s
user	0m0.221s
sys		0m1.207s


opted:
real	0m11.063s
user	0m0.304s
sys		0m1.193s

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
	
	/*
	int *ptr = NULL;
	*/
	
	for(; i < 100000; ++i)
	{
		pthread_create(&id, NULL, SetIndex, (void *)i);
		
		/* printf("value entered: %d\n", *ptr); */
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
