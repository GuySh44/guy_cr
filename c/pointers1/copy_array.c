void CopyArray(int *array, int *new_array, int array_size)
{
	int i = 0;
	for(; i < array_size; i++)
		new_array[i] = array[i];
}

