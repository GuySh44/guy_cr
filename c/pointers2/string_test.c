#include<stdio.h>
#include<string.h>
#include<strings.h>
#include"string.h"


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
	
	
	printf("\n\nnew test: strcasecmp\n");	
	printf("test cases:\n");
	printf("CASE 1: empty string\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("%d\n",strcasecmp("",""));
	
	printf("MY STRING:\n");
	printf("%d\n\n",StrCasecmp("",""));;
	
	printf("CASE 2: s1 </>/= s2 \n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("Abc aBC\t%d\n",strcasecmp("Abc","aBC"));
	printf("ABC AbC\t%d\n",strcasecmp("ABC","AbC"));
	printf("abC aBd\t%d\n",strcasecmp("abC","aBd"));
	
	printf("MY STRING:\n");
	printf("Abc aBC\t%d\n",StrCasecmp("Abc","aBC"));
	printf("ABC AbC\t%d\n",StrCasecmp("ABC","AbC"));
	printf("abC aBd\t%d\n",StrCasecmp("abC","aBd"));
	printf("\n");
	
	
	
	printf("\n\nnew test: strchr\n");	
	printf("test cases:\n");
	printf("CASE 1: find in empty string\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("%p\n",strchr("",'a'));
	
	printf("MY STRING:\n");
	printf("%p\n\n",StrChr("",'a'));
	
	printf("CASE 2: find null terminator\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("strchr_check %p\n",strchr(strchr_check,'\0'));
	
	printf("MY STRING:\n");
	printf("strchr_check  %p\n\n",StrChr(strchr_check,'\0'));
	
	printf("CASE 3: find non-existent char\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("h in cr3: %p\n",strchr("cr3",'h'));
	
	printf("MY STRING:\n");
	printf("h in cr3: %p\n\n",StrChr("cr3",'h'));
	
	
	printf("\n\nnew test: strdup\n");	
	printf("test cases:\n");
	printf("CASE 1: duplicate empty string\n\n");
	
	str_dup_original = strdup("");	
	str_dup_my = StrDup("");
	
	printf("ORIGINAL STRING:\n");
	printf("%p\n",str_dup_original);
	
	printf("MY STRING:\n");
	printf("%p\n\n",str_dup_my);
	
	free(str_dup_original);
	free(str_dup_my);
	
	printf("CASE 2: duplicate regular string\n\n");
	
	
	str_dup_original = strdup("abc");	
	str_dup_my = StrDup("abc");
	printf("ORIGINAL STRING:\n");
	printf("%s\n",str_dup_original);
	
	printf("MY STRING:\n");
	printf("%s\n\n",str_dup_my);
	
	printf("CASE 3: check free\n\n");
	
	free(str_dup_original);
	free(str_dup_my);
	
	printf("I DIDNT CRASH :)\n\n");
	
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
	
	
	printf("\n\nnew test: strncat\n");	
	printf("test cases:\n");
	printf("CASE 1: ncat two regular add null to end cause n = src-1\n\n");
	
	strncat(dest8_org,src8_org,2);
	printf("ORIGINAL STRING:\n");
	printf("%s\n",dest8_org);
	
	StrNcat(dest8_my,src8_my,2);
	printf("MY STRING:\n");
	printf("%s\n\n",dest8_my);
	
	printf("CASE 2: ncat n + 2 = src (lose one)\n\n");
	
	strncat(dest9_org,src9_org,1);
	printf("ORIGINAL STRING:\n");
	printf("%s\n",dest9_org);
	
	StrNcat(dest9_my,src9_my,1);
	printf("MY STRING:\n");
	printf("%s\n\n",dest9_my);
	
	printf("CASE 3: ncat n > src (regular)\n\n");
	
	strncat(dest10_org,src10_org,5);
	printf("ORIGINAL STRING:\n");
	printf("%s\n",dest10_org);
	
	StrNcat(dest10_my,src10_my,5);
	printf("MY STRING:\n");
	printf("%s\n\n",dest10_my);
	
	printf("\n\nnew test: strstr\n");	
	printf("test cases:\n");
	printf("CASE 1: ccbca find cbc\n\n");
	
	printf("ORIGINAL STRING:\n");
 printf("%p\t%s\n",strstr(strstr_check1,"cbc"),strstr(strstr_check1,"cbc"));
	
	printf("MY STRING:\n");
	printf("%p\t%s\n",StrStr(strstr_check1,"cbc"),StrStr(strstr_check1,"cbc"));
	
	printf("CASE 2: ccbca find empty string\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("%p\t%s\n",strstr(strstr_check1,""),strstr(strstr_check1,""));
	
	printf("MY STRING:\n");
	printf("%p\t%s\n",StrStr(strstr_check1,""),StrStr(strstr_check1,""));
	
	printf("CASE 3: aaccbcca return first cc\n\n");
	
	printf("ORIGINAL STRING:\n");
		printf("%p\t%s\n",strstr(strstr_check2,"cc"),strstr(strstr_check2,"cc"));
	
	printf("MY STRING:\n");
	printf("%p\t%s\n",StrStr(strstr_check2,"cc"),StrStr(strstr_check2,"cc"));
	
	printf("CASE 4: empty string in empty string\n\n");
	
	printf("ORIGINAL STRING:\n");
		printf("%p\t%s\n",strstr(strstr_check3,""),strstr(strstr_check3,""));
	
	printf("MY STRING:\n");
	printf("%p\t%s\n",StrStr(strstr_check3,""),StrStr(strstr_check3,""));
	
	printf("\n\nnew test: strspn\n");	
	printf("test cases:\n");
	printf("CASE 1: ""abcd"" accepting ""cba c""\n\n");
	
	printf("ORIGINAL STRING:\n");
	printf("%lu\n",strspn("abcd", "cba c"));
	
	printf("MY STRING:\n");
	printf("%lu\n\n",StrSpn("abcd", "cba c"));
	
	printf("CASE 2: ""abcd"" accepting ""cba_d""\n\n");
	printf("ORIGINAL STRING:\n");
	printf("%lu\n",strspn("abcd", "cba_d"));
	
	printf("MY STRING:\n");
	printf("%lu\n\n",StrSpn("abcd", "cba_d"));
	
	printf("CASE 3: ""abcd"" accepting empty string\n\n");
	printf("ORIGINAL STRING:\n");
	printf("%lu\n",strspn("abcd", ""));
	
	printf("MY STRING:\n");
	printf("%lu\n\n",StrSpn("abcd", ""));
	
	printf("CASE 4: abz accepting very long set of strings\n\n");
	printf("ORIGINAL STRING:\n");
	printf("%lu\n",strspn("abz", "abcdefghijklmnop"));
	
	printf("MY STRING:\n");
	printf("%lu\n\n",StrSpn("abz", "abcdefghijklmnop"));
	
	return 0;
}
