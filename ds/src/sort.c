










static void SwapInt(int* num1_p, int* num2_p)
{
	int tmp = *num1_p;
	*num1_p = *num2_p;
	*num2_p = tmp;
}

void BubbleSort(int *arr, int size)
{
	int i = 0;
	int j;
	for(; i < size - 1; ++i)
	{
		j = 0;
		for(; j < size - i - 1; ++j)
		{
			if(arr[j] > arr[j+1])
			{
				SwapInt(&arr[j], &arr[j+1]);
			}
		}
	}
}

void SelectionSort(int *arr, int size)
{
	int i = 0;
	int j = 0;
	int min_ind;
	for(; i < size; ++i)
	{
		j = i;
		min_ind = j;
		for(; j < size; ++j)
		{
			if(arr[j] < arr[min_ind])
			{
				min_ind = j;
			}
		}
		SwapInt(&arr[min_ind], &arr[i]);
	}
}

void InsertionSort(int *arr, int size)
{
	int i = 1;
	int j;
	for(; i < size; ++i)
	{
		j = i;
		for(; j > 0; --j)
		{
			if(arr[j - 1] > arr[j])
			{
				SwapInt(&arr[j - 1], &arr[j]);
			}
			else
			{
				break;
			}
		}
	}
}
