#include<stdio.h>
#include<string.h>
#include"string.h"

int main()
{
	char src[] = "abcdef";
	char dest[7];
	char short_dest[6];
	char long_dest[9];
	char emptysrc[] = "";
	char emptydest[1];
	int i = 0;
	/*
	printf("old address src:%p, dest:%p\n", (void*)src, (void*)dest);
	*/
	
	printf("check regular copy:\n");
	printf("old value src:%s, dest:%s\n", src, dest);
	StrCpy(dest,src);
	printf("new value src:%s, dest:%s\n", src, dest);
	
	printf("\n");
	
	printf("check empty string copy:\n");
	printf("old value emptysrc:%s, emptydest:%s\n", emptysrc, emptydest);
	StrCpy(emptydest,emptysrc);
	printf("new value emptysrc:%s, emptydest:%s\n", emptysrc, emptydest);
	
	printf("\n");
	
	printf("check short destination n < src\n");
	printf("old value src:");
	for(; i < 7; i++)
		printf("'%02x'",*(src+i));
	printf(", short_dest:");
	for(; i < 6; i++)
		printf("'%02x'",*(short_dest+i));
	
	
	
	printf("\n");
	StrNcpy(short_dest,src,6);
	
	
	printf("new value src:");
	for(; i < 7; i++)
		printf("'%02x'",*(src+i));
	printf(", short_dest:");
	for(; i < 6; i++)
		printf("'%02x'",*(short_dest+i));
		
		
	printf("\n");
	printf("\n");
	
	printf("check long destination n > src \n");
	printf("old value src:%s, long_dest:", src);
	for(; i < 9; i++)
		printf("%02x",*(long_dest+i));
	printf("\n");

	StrNcpy(long_dest,src,9);
	printf("new value src:%s, long_dest:", src);
	for(; i < 9; i++)
		printf("%02x",*(long_dest+i));
	printf("\n");
	
	printf("original string n compare with high n:%d\n",strncmp("abc","abd",5));
	printf("\n");
	printf("check case compare:\n");
	printf("mine:%d \n",StrCasecmp("Arz","arz"));

	printf("mine:%d \n",StrCasecmp("arz","Arz"));

	printf("mine:%d \n",StrCasecmp("arz","Arzsd"));

	
	
	
	
	return 0;
}
