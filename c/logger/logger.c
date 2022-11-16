#include"logger.h"

/* reviewer: or */
void printNum(int num)
{
	printf("%d\n",num);	
}
void firstExercise()
{
	int i = 0;
	struct print_me array[10];
	for(; i < 10; i++)
	{
		array[i].num = i;
		array[i].Print = &printNum;
		array[i].Print(array[i].num);
	}
}

void manageLogger(char *file_name)
{
	char BUFFER[1024];
	printf("Welcome to the logger, please dont overflow my buffer\n");
	while(scanf("%s\n",BUFFER) >= 0)
	{
		commands command;
		FILE *file_ptr = fopen(file_name);
		if(NULL == file_ptr)
		{
			break;
		}
		
		command = parseInput(BUFFER);
		executeLogger(BUFFER, file_ptr, command);
		
	}
	printf("%s\n", strerror(errno));
}

commands parseInput(char *buffer)
{
	
}

void executeLogger(char *buffer, FILE *file, commands command)
{

}

void appendLine(char *buffer, FILE *file, commands command)
{

}


