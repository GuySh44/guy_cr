#include<queue.h>
#include"my_utils.h"
#include<stdio.h>

int main()
{
	queue_t *my_queue;
	queue_t *my_queue_destroy = QueueCreate(5);
	int five = 5;
	int seven = 7;
	printf("TEST INT:\n");
	printTest("my_queue_destroy capacity is 5",!(QueueCapacity(my_queue_destroy) == 5));
	printTest("Destroy normal queue:",QueueDestroy(my_queue_destroy));
	my_queue = QueueCreate(2);
	printTest("my_queue capacity is 2",!(QueueCapacity(my_queue) == 2));
	QueuePush(my_queue,&five);
	printTest("my_queue capacity is 2",!(QueueCapacity(my_queue) == 2));
	printTest("Did my five survive?",!(*((int*)QueuePeek(my_queue)) == 5));
	QueuePush(my_queue,&seven);
	printTest("my_queue capacity is 2",!(QueueCapacity(my_queue) == 2));
	printTest("It should'nt be empty",(!IsQueueEmpty(my_queue) == 0));
	printTest("Lets see paul sevens card... OMG...",!(*((int*)QueuePeek(my_queue)) == 5));
	printTest("It even has a watermark...",!(QueueSize(my_queue) == 2));
	QueuePop(my_queue);
	printTest("my_queue capacity is 2",!(QueueCapacity(my_queue) == 2));
	printTest("It should'nt be empty",(!IsQueueEmpty(my_queue) == 0));
	printTest("Did my five survive again?",!(*((int*)QueuePeek(my_queue)) == 7));
	printTest("After I pop once",!(QueueSize(my_queue) == 1));
	QueuePop(my_queue);
	printTest("my_queue capacity is 2",!(QueueCapacity(my_queue) == 2));
	printTest("It should be empty",!(IsQueueEmpty(my_queue) == 1));
	
	QueueDestroy(my_queue);
	
	return 0;
}
