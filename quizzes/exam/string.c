#include <stddef.h>
#include <stdio.h>
#include <string.h>

size_t StrLen(const char *str)
{
	if(*str == '\0')
	{
		return 0;
	}
	
	return StrLen(++str) + 1;
}

int StrCmp(const char *str1, const char *str2)
{
	while(*str1 == *str2 && *str1 != '\0')
	{
		++str1;
		++str2;
	}
	
	return *str1 - *str2;
}

char *StrNcpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;
	char *dest_start = dest;
	
	while (*src != '\0' && n > 0)
	{
		*dest++ = (char)*src++;
		--n;
	}
	
	for(; i < n; ++i)
	{
		*(dest++) = '\0';
	}
	
	return dest_start;
}

char *StrCpy(char *dest, const char *src)
{
	return StrNcpy(dest, src, StrLen(src) + 1);
}

char *StrCat(char *dest, const char *src)
{
	char *dest_start = dest;
	
	while(*(dest) != '\0')
	{
		++dest;
	}
	StrCpy(dest, src);
	return dest_start;
}

int main()
{
	extern char* strdup(const char*);
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
	
	char dest6_org[7] = {'a','b','c','d','\0'};
	char* src6_org = "ef";
	char dest6_my[7] = {'a','b','c','d','\0'};
	char* src6_my = "ef";
	
	char dest7_org[7] = {'a','b','c','d','\0'};
	char* src7_org = "";
	char dest7_my[7] = {'a','b','c','d','\0'};
	char* src7_my = "";
	
	char dest8_org[7] = {'a','b','c','d','\0'};
	char* src8_org = "ef";
	char dest8_my[7] = {'a','b','c','d','\0'};
	char* src8_my = "ef";
	
	char dest9_org[7] = {'a','b','c','d','\0'};
	char* src9_org = "ef";
	char dest9_my[7] = {'a','b','c','d','\0'};
	char* src9_my = "ef";
	
	char dest10_org[7] = {'a','b','c','d','\0'};
	char* src10_org = "ef";
	char dest10_my[7] = {'a','b','c','d','\0'};
	char* src10_my = "ef";
	
	const char* strchr_check = "abc";
	
	const char* strstr_check1 = "ccbca";
	
	const char* strstr_check2 = "aaccbcca";
	
	const char* strstr_check3 = "";
	
	const char* strstr_check4 = "ac";
	
	char* str_dup_original, *str_dup_my;

	
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
	printf("%d\n",strcmp("",""));
	
	printf("MY STRING:\n");
	printf("%d\n\n",StrCmp("",""));;
	
	
	printf("CASE 2: s1 </>/= s2 regular cmp\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("abc abc\t%d\n",strcmp("abc","abc"));
	printf("abd abc\t%d\n",strcmp("abd","abc"));
	printf("abd abc\t%d\n",strcmp("abc","abd"));
	
	printf("MY STRING:\n");
	printf("abc abc\t%d\n",StrCmp("abc","abc"));
	printf("abd abc\t%d\n",StrCmp("abd","abc"));
	printf("abd abc\t%d\n",StrCmp("abc","abd"));
	printf("\n");
	
	printf("CASE 3: s1 </>/= s2 high n cmp\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("abc abc\t%d\n",strcmp("abc","abc"));
	printf("abd abc\t%d\n",strcmp("abd","abc"));
	printf("abd abc\t%d\n",strcmp("abc","abd"));
	
	printf("MY STRING:\n");
	printf("abc abc\t%d\n",StrCmp("abc","abc"));
	printf("abd abc\t%d\n",StrCmp("abd","abc"));
	printf("abd abc\t%d\n",StrCmp("abc","abd"));
	printf("\n");
	
	printf("CASE 4: s1 </>/= s2 low n cmp\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("abc abc\t%d\n",strcmp("abcd","abcd"));
	printf("abd abc\t%d\n",strcmp("abdc","abcd"));
	printf("abd abc\t%d\n",strcmp("abcdddd","abd"));
	
	printf("MY STRING:\n");
	printf("abc abc\t%d\n",StrCmp("abcd","abcd"));
	printf("abd abc\t%d\n",StrCmp("abdc","abcd"));
	printf("abd abc\t%d\n",StrCmp("abcdddd","abd"));
	printf("\n");
	
	
	printf("\n\nnew test: strcat\n");	
	printf("test cases:\n");
	printf("CASE 1: cat two regular exact size\n\n");
	
	strcat(dest6_org,src6_org);
	printf("ORIGINAL STRING:\n");
	printf("%s\n",dest6_org);
	
	StrCat(dest6_my,src6_my);
	printf("MY STRING:\n");
	printf("%s\n\n",dest6_my);
	
	printf("CASE 2: cat empty src to dest\n\n");
	
	strcat(dest7_org,src7_org);
	printf("ORIGINAL STRING:\n");
	printf("%s\n",dest7_org);
	
	StrCat(dest7_my,src7_my);
	printf("MY STRING:\n");
	printf("%s\n\n",dest7_my);
	
	
	
	return 0;
}
