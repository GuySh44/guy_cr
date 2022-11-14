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





void envExercise(char *envp[])
{
	char **new_env = envCreate(envp);
	envCopy(new_env,envp);
	envFree(new_env);
}

char **envCreate(char *envp[])
{
	size_t env_size = envLen(envp);
	char **new_env = malloc(sizeof(char*) * env_size);
	int i = 0;
	if (!new_env)
		return NULL;
	while (envp[i])
	{
		new_env[i] = malloc(strlen(envp[i]) + 1);
		if (!new_env[i])
		{
			i--;
			while (i >= 0)
			{
				free(new_env[i]);
				i--;
			}		
			return NULL;
		}
		i++;
	}
	return new_env;
}


size_t envLen(char *envp[])
{
	size_t count = 0;
	while (*envp++)
	{
		count++;
	}
	return count;
}

void envCopy(char **dest, char *src[])
{
	size_t i = 0;
	while(src[i])
	{
		strcpy(dest[i],src[i]);
		i++;
	}
}

void envFree(char **env)
{
	int i = 0;
	while (env[i])
	{
		free(env[i++]);
	}
	free(env);
}
