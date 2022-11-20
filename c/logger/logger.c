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

reviewer: raz
20/11/2022
*/

static void insertCommands(commands *ex2_commands)
{
	ex2_commands[0].command = "-remove\n";
	ex2_commands[0].Compare = &strcmp;
	ex2_commands[0].Execute = &executeRemove;
	ex2_commands[1].command = "-count\n";
	ex2_commands[1].Compare = &strcmp;
	ex2_commands[1].Execute = &executeCount;
	ex2_commands[2].command = "-exit\n";
	ex2_commands[2].Compare = &strcmp;
	ex2_commands[2].Execute = &executeExit;
	ex2_commands[3].command = "<";
	ex2_commands[3].Compare = &CmpStartAppend;
	ex2_commands[3].Execute = &executeStartAppend;
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
	argc = argc;	
	printf("Welcome to the logger, please dont overflow my buffer\n");
	while(NULL != fgets(BUFFER, BUFFER_SIZE, stdin))
	{
		size_t command_index;
		command_index = parseInput(BUFFER, ex2_commands);
		if(Fail == (*(ex2_commands + command_index)).Execute(BUFFER, file_name))
		{
			printf("error\n");
		}
	}
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


FILE* openFile(char *file_name, size_t command_index)
{
	FILE *file_ptr;
	switch(command_index)
	{
		case COUNT_INDEX:
			file_ptr = fopen(file_name, "r+");
			break;
		case START_APPEND_INDEX:
			file_ptr = fopen(file_name, "r+");
			break;
		case APPEND_INDEX:
			file_ptr = fopen(file_name, "a");
			break;
	}
	if(NULL == file_ptr)
	{
		printf("error opening file\n");
		return NULL;
	}
	return file_ptr;
}

void closeFile(FILE *file)
{
	if(0 != fclose(file))
	{
		printf("error closing file\n");
		return;
	}
}

OperStatus executeRemove(char *buffer, char *file_name)
{	
	buffer = buffer;
	if(remove(file_name) == 0)
	{
		return Success;
	}
	return Fail; 
}

OperStatus executeCount(char *buffer, char *file_name)
{
	size_t count = 0;
	char c;
	FILE *file = openFile(file_name, COUNT_INDEX);
	buffer = buffer;
	if (NULL == file)
	{
		return Fail;
	}
	c = fgetc(file);
	while(EOF != c)
	{
		if(c == '\n')
		{
			++count;
		}
	c = fgetc(file);
	}
	printf("num of lines: %lu\n",count);
	closeFile(file);
	return Success;
}

OperStatus executeExit(char *buffer, char *file_name)
{
	file_name = file_name;
	buffer = buffer;
	exit(0);
	return Success;
}

OperStatus executeStartAppend(char *buffer, char *file_name)
{
	FILE *file;
	if(-1 == rename(file_name,"tmptmp"))
	{
		if (ENOENT == errno){
			executeAppend(buffer+1,file_name);
			return Success;
		}
		else
		{
			return Fail;
		}
	}
	executeAppend(buffer+1,file_name);
	file = openFile("tmptmp", START_APPEND_INDEX);
	while(NULL != fgets(buffer, BUFFER_SIZE, file))
	{
		executeAppend(buffer, file_name);
	}
	if (feof(file))
	{
		remove("tmptmp");
	}
	else
	{
		rename("tmptmp", file_name);
		printf("error\n");
	}
	closeFile(file);
	return Success;
}

OperStatus executeAppend(char *buffer, char *file_name)
{
	FILE *file = openFile(file_name, APPEND_INDEX);
	if (NULL == file)
	{
		return Fail;
	}
	fseek(file, 0, SEEK_END);
	if(fputs(buffer, file) < 0)
	{
		return Fail;
	}
	closeFile(file);
	return Success;
}

OperStatus executeEmpty(char *buffer, char *file_name)
{
	buffer = buffer;
	file_name = file_name;
	return Success;
}


int CmpStartAppend(const char *str1, const char *str2)
{
	return strncmp(str1, str2, 1);
} 










