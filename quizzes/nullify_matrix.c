#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>

void NullifyMatrix(int matrix[][10], size_t rows, size_t cols)
{
	size_t i = 0, j = 0;
	size_t *marked_cols = (size_t*)malloc(sizeof(size_t)*cols);
	size_t *marked_rows = (size_t*)malloc(sizeof(size_t)*rows);
	for(; i < rows; ++i)
	{
		marked_rows[i] = 0;
	}
	for(; j < cols; ++j)
	{
		marked_cols[j] = 0;
	}
	i = 0;
	for(;i < rows; ++i)
	{
		j = 0;
		for(;j < cols; ++j)
		{
			if(matrix[i][j] == 0)
			{
				marked_cols[j] = 1;
				marked_rows[i] = 1;
			}
		}
	}
	i = 0;
	for(;i < rows; ++i)
	{
		j = 0;
		for(;j < cols; ++j)
		{
			if(marked_cols[j] == 1 || marked_rows[i] == 1)
			{
				matrix[i][j] = 0;
			}
		}
	}
	free(marked_cols);
	free(marked_rows);
}

int main()
{
	int matrix[10][10];
	int i = 0, j = 0;
	for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            matrix[i][j] = 2;
        }
    }
    i = 0, j = 0;
	matrix[5][7] = 0;
	matrix[1][1] = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    i = 0, j = 0;
	NullifyMatrix(matrix,10,10);
	for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
