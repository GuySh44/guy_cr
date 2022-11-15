#include "arrays_pointers.h"

int main(int argc, char *argv[], char *envp[])
{	
	int arr1[4][4] = {{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
	int res[4];
	/*
	int *arr2[4];
	int **arr3;
	*/
	int k = 0, i = 0;
	printf("index for 5 is: %lu\n",josephus(5,0));
	printf("index for 30 is:%lu\n",josephus(30,0));	
	printf("index for 40 is: %lu\n",josephus(40,0));
	printf("index for 41 is:%lu\n",josephus(41,0));	
	printf("index for 50 is: %lu\n",josephus(50,0));
	printf("index for 100 is: %lu\n",josephus(100,0));
	printCTypes();
	/*
	array1(arr1);
	array2(arr2);
	array3(arr3);
	*/
	rowCalc(arr1, res, 4, 4);
	for (; k < 4; k++)
	{
		printf("%d ",res[k]);
	}
	
	printf("number of argunments: %d\n",argc);
	printf("string of first argunment: %s\n",argv[0]);
	printf("string of environment variable: %s\n",envp[0]);
	
	
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	
	envExercise(envp);
	
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	
	while (envp[i])
	{
		printf("%s\n",envp[i]);
		i++;
	}
	return 0;
}

