#include"arrays_pointers.h"
size_t josephus(size_t n, size_t start)
{
	size_t i=1;
	size_t current = start;
	size_t *array = malloc(sizeof(size_t)* n);
	size_t *tmp_array = array;
	for(;i < n; i++)
		*tmp_array++ = i;
	*tmp_array = 0;
	while(array[current] != current)
	{
		array[current] = array[array[current]];
		current = array[current];
	}
	free(array);
	return current;
}

void printCTypes()
{
	printf("signed char %lu\n",sizeof(signed char));
	printf("unsigned char %lu\n",sizeof(unsigned char));
	printf("char %lu\n",sizeof(char));
	printf("short int %lu\n",sizeof(short int));
	printf("unsigned short int %lu\n",sizeof(unsigned short int));
	printf("int %lu\n",sizeof(int));
	printf("unsigned int %lu\n",sizeof(unsigned int));
	printf("long int %lu\n",sizeof(long int));
	printf("unsigned long int %lu\n",sizeof(unsigned long int));
	printf("float %lu\n",sizeof(float));
	printf("double %lu\n",sizeof(double));
	printf("long double %lu\n",sizeof(long double));
	printf("size_t %lu\n",sizeof(size_t));
	printf("pointer %lu\n",sizeof(size_t*));
}
/*
void array1(int array[][4])
{
	printf("array[][] size is: %lu\n",sizeof(array));
}

void array2(int **array)
{
	printf("**array size is: %lu\n",sizeof(array));
}

void array3(int *array[])
{
	printf("*array[] size is: %lu\n",sizeof(array));
}
*/
void rowCalc(int array[][4], int *res, int row_size, int col_size)
{
	int i=0;
	for(; i < row_size; i++)
	{
		int j=0;
		int sum = 0;
		for(; j < col_size; j++)
		{
			sum += array[i][j];
		}
		*res++ = sum;
	}
}



static char **envCreate(char *envp[], size_t env_size)
{
	char **new_env = malloc(sizeof(char*) * (env_size));
	char **new_start = new_env;
	if (!new_env)
		return NULL;
	while (NULL != *envp)
	{
		*new_env = malloc(strlen(*envp) + 1);
		if (NULL == *new_env)
		{
			new_env--;
			while (new_start != new_env)
			{
				free(*new_env);
				new_env--;
			}		
			return NULL;
		}
		new_env++;
		envp++;
	}
	return new_start;
}


static size_t envLen(char *envp[])
{
	char **start = envp;
	while (NULL != *envp)
		envp++;
	return (envp-start);
}

static void envCopy(char **new_envp, char *envp[])
{
	while(NULL != *envp)
	{
		char *tmp_new_envp = *new_envp;
		char *tmp_envp = *envp;
		while('\0' != *tmp_envp)
		{
			*tmp_new_envp = tolower(*tmp_envp);
			(tmp_envp)++;
			(tmp_new_envp)++;	
		}	
		*tmp_new_envp = '\0';
		new_envp++;
		envp++;
	}
	new_envp = NULL;
}

static void envFree(char *env[], size_t env_size)
{
	char **env_running = env;
	char **end = env + env_size;
	while (env_running != end)
	{
		free(*env_running);
		*env_running = NULL;
		env_running++;
	}
	free(env);
}

static void envPrint(char **new_envp, size_t env_size)
{
	char **end = new_envp + env_size;
	while (new_envp != end)
	{
		printf("%s\n",*new_envp);
		new_envp++;
	}
}

void envExercise(char *envp[])
{
	size_t env_size = envLen(envp);
	char **new_env = envCreate(envp, env_size);
	envCopy(new_env,envp);
	envPrint(new_env,env_size);
	envFree(new_env,env_size);
}


