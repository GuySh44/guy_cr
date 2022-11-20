#include<string.h>
#include<stdio.h>

int IsRotation(char* s1, char* s2)
{
	int i = 0;
	int s1_len = strlen(s1);
	int s2_len = strlen(s2);
	if (s1_len != s2_len)
	{
		return 0;
	}
	for(; i < s2_len; i++)
	{
		int j = 0;
		while(s1[j%s1_len] == s2[(i+j)%s2_len] && j <= s1_len)
		{
			if(j == s1_len)
			{
				return 1;
			}
			j++;
		}
	}
	return 0;
}




int main()
{
	printf("Is 45123 rotation of 12345?\t%d\n",IsRotation("12345","45123"));
	printf("Is 123412 rotation of 121234?\t%d\n",IsRotation("121234","123412"));
	return 0;
}
