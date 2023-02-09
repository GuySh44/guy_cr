#include <stdio.h> /* fgets printf */
#include <string.h> /* strcmp strtok strlen */
#include <stdlib.h> /* atoi */
#include <stddef.h> /* size_t */
#include <fcntl.h>	/* For O_* constants */
#include <semaphore.h>	/* sem_getvalue sem_wait sem_post sem_open sem_close */
#include <sys/types.h>	/* key_t, sem_t, pid_t */
#include <assert.h>

/* Doniel */

#define BUFFER_SIZE 256
#define NUM_OF_WORDS 5

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

/* Calculate semaphore value */
static int SemCalcValue(sem_t *sem)
{
	int sem_value = 0;
	int status = 0; 
	
	assert(sem);
	
	status = sem_getvalue(sem, &sem_value);
	
	if(-1 == status)
	{
		return status;
	}
	
	return sem_value;
}


/* decrement semaphor value, if its [undo] update temp_value for change before exit */
static int SemDecrement(sem_t *sem, int *temp_value_ptr, int num, const char *param)
{
	int retval_wait = 0;
	int i = 0;
	
	assert(sem);
	
	
	if(NULL != param && 0 == strcmp((char*)param, "[undo]"))
	{
		*temp_value_ptr -= num;
	}
	
	for(; i < num; ++i)
	{
		retval_wait = sem_wait(sem);
		if(0 != retval_wait)
		{
			return retval_wait;
		}
	}
	
	return 0;
}

/* increment semaphor value, if its [undo] update temp_value for change before exit */
static int SemIncrement(sem_t *sem, int *temp_value_ptr, int num, const char *param)
{
	int retval_post = 0;
	int i = 0;
	
	assert(sem);
	
	if(NULL != param && 0 == strcmp((char*)param, "[undo]"))
	{
		*temp_value_ptr += num;
	}

	for(; i < num; ++i)
	{
		retval_post = sem_post(sem);
		if(0 != retval_post)
		{
			return retval_post;
		}
	}
	
	return 0;
}

/* close semaphor, update to wanted semaphor value incase we had [undo] operations */
static int SemClose(sem_t *sem, int temp_value)
{
	int retval_close = 0;
	
	assert(sem);
	
	if(temp_value > 0)
	{
		SemDecrement(sem, &temp_value, temp_value, NULL);
	}
	else if(temp_value < 0)
	{
		SemIncrement(sem, &temp_value, (-1)*temp_value, NULL);
	}
	
	retval_close = sem_close(sem);
	
	return retval_close;
}

int main(int argc, char *argv[])
{
	char buffer[BUFFER_SIZE] = {0};
	char *parsed[NUM_OF_WORDS] = {0};
	int command = 0;
	int temp_value = 0;
	int num = 0;
	int value = 0;
	
	sem_t *sem = NULL;
	
	sem = sem_open(argv[1], O_CREAT, 0644, 0);
	
	if(SEM_FAILED == sem)
	{
		return 1;
	}
	
	while(NULL != fgets(buffer, BUFFER_SIZE, stdin))
	{
		buffer[strlen(buffer) - 1] = '\0';
		
		ParseCommand(buffer, parsed);
		
		command = (int)(*parsed[0]);
		
		switch(command)
		{
			case 'X':
				if(-1 == SemClose(sem, temp_value))
				{
					continue;
				}
				return 0; 
				break;
			
			case 'V':
				value = SemCalcValue(sem);
				if(-1 == value)
				{
					return -1
				}
				printf("%d\n", value);
				break;
				
			case 'D':
				num = atoi(parsed[1]);
				if(-1 == SemDecrement(sem, &temp_value, num, parsed[2]))
				{
					return -1;
				}
				break;
				
			case 'I':
				num = atoi(parsed[1]);
				if(-1 == SemIncrement(sem, &temp_value, num, parsed[2]))
				{
					return -1;
				}
				break;
				
			default:
				break;
		}
		
		/* clear buffer */
		memset(buffer, '\0', BUFFER_SIZE);
		
		/* clear parsed */
		memset(parsed, 0, NUM_OF_WORDS * sizeof(*parsed));
		
	}
	
	return 0;
	
	(void)argc;
}


