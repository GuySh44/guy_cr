#include<stdio.h>
#include"string.h"
#include<string.h>

int main()
{
	char src[] = "lalala";
	char dest[7];
	
	char emptysrc[] = "";
	char emptydest[1];
	/*
	printf("old address src:%p, dest:%p\n", (void*)src, (void*)dest);
	*/
	printf("old value src:%s, dest:%s\n", src, dest);
	StrCpy(dest,src);
	printf("new value src:%s, dest:%s\n", src, dest);
	
	printf("\n");
	
	printf("old value emptysrc:%s, emptydest:%s\n", emptysrc, emptydest);
	StrCpy(emptydest,emptysrc);
	printf("new value emptysrc:%s, emptydest:%s\n", emptysrc, emptydest);
	return 0;
}
