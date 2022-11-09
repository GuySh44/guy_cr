#include<stdio.h>
#include<string.h>
#include"string.h"

/*
void new_test(char* new_test,
{
	printf("new test: %s\n", new_test);
	printf("original string class:

}

*/
int main()
{
	char dest1_org[5];
	char* src1_org = "abcd";
	char dest1_my[5];
	char* src1_my = "abcd";
	
	char dest2_org[7];
	char* src2_org = "abcd";
	char dest2_my[7];
	char* src2_my = "abcd";
	
	char dest3_org[5];
	char* src3_org = "aceg";
	char dest3_my[5];
	char* src3_my = "aceg";
	
	char dest4_org[5];
	char* src4_org = "aceg";
	char dest4_my[5];
	char* src4_my = "aceg";
	
	char dest5_org[7];
	char* src5_org = "aceg";
	char dest5_my[7];
	char* src5_my = "aceg";
	
	dest4_org[4] = 'f';
	dest4_my[4] = 'f';
	
	
	printf("new test: strcpy\n");	
	printf("test cases:\n");
	printf("CASE 1: dest exactly right\n\n");
	
	printf("ORIGINAL STRING:\n");
	strcpy(dest1_org,src1_org);
	printf("src: %s\t dest: %s\n\n", src1_org, dest1_org);
	
	printf("MY STRING:\n");
	StrCpy(dest1_my,src1_my);
	printf("src: %s\t dest: %s\n\n", src1_my, dest1_my);
	
	
	printf("CASE 2: dest larger than src\n\n");
	
	printf("ORIGINAL STRING:\n");
	strcpy(dest2_org,src2_org);
	printf("src: %s\t dest: %s\n\n", src2_org, dest2_org);
	
	printf("MY STRING:\n");
	StrCpy(dest2_my,src2_my);
	printf("src: %s\t dest: %s\n\n", src2_my, dest2_my);
	

	printf("\n\nnew test: strncpy\n");	
	printf("test cases:\n");
	printf("CASE 1: dest exactly right\n\n");
	
	printf("ORIGINAL STRING:\n");
	strncpy(dest3_org,src3_org,5);
	printf("src: %s\t dest: %s\n\n", src3_org, dest3_org);
	
	printf("MY STRING:\n");
	StrNcpy(dest3_my,src3_my,5);
	printf("src: %s\t dest: %s\n\n", src3_my, dest3_my);
	
	
	printf("CASE 2: n < src\n\n");
	
	printf("ORIGINAL STRING:\n");
	strncpy(dest4_org,src4_org,4);
	printf("src: %s\t dest: %s\n\n", src4_org, dest4_org);
	
	printf("MY STRING:\n");
	StrNcpy(dest4_my,src4_my,4);
	printf("src: %s\t dest: %s\n\n", src4_my, dest4_my);
	
	
	printf("CASE 3: src < n\n\n");
	
	printf("ORIGINAL STRING:\n");
	strncpy(dest5_org,src5_org,7);
	printf("src: %s\t dest: %s%x%x\n\n", src5_org, dest5_org,dest5_org[5],dest5_org[6]);
	
	printf("MY STRING:\n");
	StrNcpy(dest5_my,src5_my,7);
	printf("src: %s\t dest: %s%x%x\n\n", src5_my, dest5_my,dest5_my[5],dest5_my[6]);
	
	
	printf("\n\nnew test: strcmp\n");	
	printf("test cases:\n");
	printf("CASE 1: empty string\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("%d\n",strncmp("","",3));
	
	printf("MY STRING:\n");
	printf("%d\n\n",StrNcmp("","",3));;
	
	
	printf("CASE 2: s1 </>/= s2 regular cmp\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("abc abc\t%d\n",strncmp("abc","abc",4));
	printf("abd abc\t%d\n",strncmp("abd","abc",4));
	printf("abd abc\t%d\n",strncmp("abc","abd",4));
	
	printf("MY STRING:\n");
	printf("abc abc\t%d\n",StrNcmp("abc","abc",4));
	printf("abd abc\t%d\n",StrNcmp("abd","abc",4));
	printf("abd abc\t%d\n",StrNcmp("abc","abd",4));
	printf("\n");
	
	printf("CASE 3: s1 </>/= s2 high n cmp\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("abc abc\t%d\n",strncmp("abc","abc",7));
	printf("abd abc\t%d\n",strncmp("abd","abc",7));
	printf("abd abc\t%d\n",strncmp("abc","abd",7));
	
	printf("MY STRING:\n");
	printf("abc abc\t%d\n",StrNcmp("abc","abc",7));
	printf("abd abc\t%d\n",StrNcmp("abd","abc",7));
	printf("abd abc\t%d\n",StrNcmp("abc","abd",7));
	printf("\n");
	
	printf("CASE 4: s1 </>/= s2 low n cmp\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("abc abc\t%d\n",strncmp("abcd","abcd",3));
	printf("abd abc\t%d\n",strncmp("abdc","abcd",3));
	printf("abd abc\t%d\n",strncmp("abcdddd","abd",3));
	
	printf("MY STRING:\n");
	printf("abc abc\t%d\n",StrNcmp("abcd","abcd",3));
	printf("abd abc\t%d\n",StrNcmp("abdc","abcd",3));
	printf("abd abc\t%d\n",StrNcmp("abcdddd","abd",3));
	printf("\n");
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	char src[] = "abcdef";
	char dest[7];
	char short_dest[6];
	char long_dest[9];
	char emptysrc[] = "";
	char emptydest[1];
	int i = 0;
	printf("old address src:%p, dest:%p\n", (void*)src, (void*)dest);
	
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

	*/
	
	
	
	return 0;
}
