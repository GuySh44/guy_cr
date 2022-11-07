void SwapInt(int* a, int* b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
int main()
{
	int a = 3, b = 5;
	SwapInt(&a, &b);
	return 0;
}
