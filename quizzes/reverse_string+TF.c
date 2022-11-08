#include<stdio.h>

void TF(int num)
{
	int i = 1;
	for(; i < num; i++)
	{
		int flag = 0;
		if (i%3 == 0)
		{
			printf("T");
			flag = 1;
		}
		if (i%5 == 0)
		{
			printf("F");
			flag = 1;
		}
		if (flag == 0)
			printf("%d", i);
		printf("\n");
	}
}


void ReverseString(char* s, int s_len)
{
	int diff = 'a' - 'A';
	int i = 0;
	for(; i < s_len/2; i++)
	{
		char first_tmp = s[i];
		char last_tmp = s[s_len-1-i];
		if (first_tmp >= 'A' && first_tmp <= 'Z')
			first_tmp += diff;
		if (last_tmp >= 'A' && last_tmp <= 'Z')
			last_tmp += diff;
		s[i] = last_tmp;
		s[s_len-1-i] = first_tmp;
	}
}





int main()
{
	//char *test = "lmao"; doesnt work, seg fault 
	char test[] = "lmao";
	ReverseString(test,4);
	printf("%s\n", test);
	TF(16);
	return 0;
}
