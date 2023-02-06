#include <stdio.h> /* fgets printf */
#include <string.h> /* strcmp strtok strlen */
#include <stdlib.h> /* atoi system */
#include <stddef.h> /* size_t */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <unistd.h> /* fork wait */
#include <signal.h> /* psignal */
#include <errno.h> /* errno perror */
#include <assert.h>


#define BUFFER_SIZE 1024
#define COMMAND_SIZE 4
#define NUM_OF_WORDS 32

/* Reviewer: Ravidioli */


/* ... */
static void PrintCreationPrompt()
{
	printf("Please enter proccess creation method\n");
	printf("Enter 1 for 'fork'\n");
	printf("Enter 2 for 'system'\n");	
}


/* recieve input from user to choose 'fork' or 'system', put the corresponding command number into command */
static int GetCreationMethod(void *buffer, size_t buffer_size, FILE *stream, int *command)
{

	assert(buffer);
	assert(stream);
	assert(command);
	
	if(NULL == fgets(buffer, buffer_size, stream))
	{
		return 1;
	}
	
	*command = atoi(buffer);
	
	return 0;
}


/* parse a string from buffer into an argv structure */
static void ParseCommand(char *buffer, char *argv[])
{
	size_t i = 0;
	char *token = NULL;
	
	assert(buffer);
	assert(argv);
	
	while(' ' == *buffer)
	{
		++buffer;
	}
	
	token = strtok(buffer, " ");
	
	while(NULL != token)
	{
		argv[i] = token;
		++i;
		token = strtok(NULL, " ");
	}
	
}  

int main()
{
	char buffer[BUFFER_SIZE] = {0};
	char command[COMMAND_SIZE] = {0};
	char *parsed[NUM_OF_WORDS] = {0};
	int command_switch = 0;
	int status = 0;
	pid_t child_id = {0};
	
	/* print hello */
	PrintCreationPrompt();
	
	/* recieve wanted proccess creation method */
	status = GetCreationMethod(command, COMMAND_SIZE, stdin, &command_switch);
	if(status)
	{
		return status;
	}
	
	/* REPL */
	while(1)
	{
		printf("Enter the command for execution\n");
		
		/* clear buffer */
		memset(buffer, '\0', BUFFER_SIZE);
		
		/* clear parsed */
		memset(parsed, 0, NUM_OF_WORDS * sizeof(*parsed));
		
		if(NULL != fgets(buffer, BUFFER_SIZE, stdin))
		{
			
			/* get rid of '/n' */
			buffer[strlen(buffer) - 1] = '\0';
			
			if(0 == strcmp(buffer, "exit"))
			{
				return 0;
			}
			
			switch(command_switch)
			{
				/* fork method */
				case 1:
				
					ParseCommand(buffer, parsed);
					
					/* forked child */
					child_id = fork();
					
					if(0 == child_id)
					{
						if(-1 == execvp(parsed[0],(parsed)))
						{
							perror(NULL);
							return errno;
						}
						return 0;
					}
					/* parent */
					else
					{
						waitpid(child_id, &status, 0);
						/* non zero exit status */
						if(WEXITSTATUS(status))
						{
							printf("Exit status: %d\n", WEXITSTATUS(status));
						}
						/* process recieved signal */
						else if (WIFSIGNALED(status))
						{
							printf("Exit signal: %d\n", WTERMSIG(status));
						}
					}
					break;
					
				/* system method */
				case 2:
					
					status = system(buffer);
					
					if(status)
					{
						printf("Process error: %d\n", status);
					}
					break;
					
				/* wrong method number input */
				default:
					printf("No such method\n");
					return 2;
					break;
			}
		}
	}
	
	return 0;
}