#include <stdio.h>

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
	if(1 == n)
	{
		printf("Disk 1 moved from %c to %c\n", from_rod, to_rod);
		return;
	}
	towerOfHanoi(n-1, from_rod, aux_rod, to_rod);
	printf("Disk %d moved from %c to %c\n",n, from_rod, to_rod);
	towerOfHanoi(n-1, aux_rod, to_rod, from_rod);
}

int main()
{
	towerOfHanoi(4, 'A', 'C', 'B');
	return 0;
}
