#include"functions.h"
int main()
{
	int i;
	printf("choose implementation:\n[1] LUT\n[2] switch\n[3] if/else\n");
	scanf("%d",&i);
	printf("Excellent choice\n");
	switch(i)
	{
		case 1:
			lutImplement();
			break;
		case 2:
			switchImplement();
			break;
		case 3:
			ifImplement();
			break;
	}
	return 0;
}
