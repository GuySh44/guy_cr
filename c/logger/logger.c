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

/*

EXERCISE 2

*/

static void insertCommands(commands *ex2_commands)
{
	ex2_commands[0].command = "-remove\n";
	ex2_commands[0].Compare = &strcmp;
	ex2_commands[0].Execute = &executeEmpty;
	ex2_commands[1].command = "-count\n";
	ex2_commands[1].Compare = &strcmp;
	ex2_commands[1].Execute = &executeEmpty;
	ex2_commands[2].command = "-exit\n";
	ex2_commands[2].Compare = &strcmp;
	ex2_commands[2].Execute = &executeEmpty;
	ex2_commands[3].command = "<";
	ex2_commands[3].Compare = &strcmp;
	ex2_commands[3].Execute = &executeEmpty;
	ex2_commands[4].command = "append";
	ex2_commands[4].Compare = &strcmp;
	ex2_commands[4].Execute = &executeAppend;
}

int main(int argc,char *argv[])
{
	char BUFFER[BUFFER_SIZE];
	char *file_name = argv[1];
	commands ex2_commands[NUM_OF_COMMANDS];
	insertCommands(ex2_commands);
	
	printf("Welcome to the logger, please dont overflow my buffer\n");
	while(NULL != fgets(BUFFER, BUFFER_SIZE, stdin))
	{
		size_t command_index;
		command_index = parseInput(BUFFER, ex2_commands);
		(*(ex2_commands + command_index)).Execute(BUFFER, file_name);

	}
	printf("%s\n", strerror(errno));
	return 0;
}


size_t parseInput(char *buffer, commands *ex2_commands)
{
	commands *start = ex2_commands;
	while (0 != strcmp("append",(*ex2_commands).command))
	{
		if(0 == (*ex2_commands).Compare((*ex2_commands).command, buffer))
		{
			break;
		}
		ex2_commands++;
	}

	return ex2_commands - start;
}


void executeAppend(char *buffer, char *file_name)
{
	FILE *file = openFile(file_name, APPEND_INDEX);
	if(fputs(buffer, file) < 0)
	{
		printf("%s\n", strerror(errno));
		exit(errno);
	}
	fseek(file, 0, SEEK_END);
	closeFile(file);
}

FILE* openFile(char *file_name, size_t command_index)
{
	FILE *file_ptr;
	switch(command_index)
	{
		case APPEND_INDEX:
			file_ptr = fopen(file_name, "a");
			if(NULL == file_ptr)
			{
				printf("%s\n", strerror(errno));
				exit(errno);
			}
			break;
	}
	return file_ptr;
}

void closeFile(FILE *file)
{
	if(0 != fclose(file))
	{
		printf("%s\n", strerror(errno));
		exit(errno);
	}
}

void executeEmpty(char *buffer, char *file_name){}
