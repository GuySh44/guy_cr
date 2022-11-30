#include"atoi_itoa.h"
#include"../../my_tests/utils.h"
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>

static void atoiCompare(char *str)
{
	printTest("My atoi is better!",!(atoi(str) == stringToInt(str,10)));
}

int main()
{
	char arr1[8] = {'a' , 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
	char arr2[6] = {'b', 'c', 'd', 'e', 'f', 'g'};	
	char arr3[6] = {'d', 'e', 'f', 'g', 'z', 'h'};
	
	int i = 2;
	char str1[11];
	char str2[12];
	char str3[3];
	char str4[4];
	char str5[4];
	char str6[5];
	char str7[5];
	char str8[6];
	char str9[5];
	char str10[6];
	char str11[10];
	char str12[11];
	char str13[5];
	char str14[6];
	char str15[4];
	char str16[5];
	
	i = 10;
	intToString(INT_MAX,str1,i);
	intToString(INT_MIN,str2,i);
	intToString(10,str3,i);
	intToString(-10,str4,i);
	intToString(100,str5,i);
	intToString(-100,str6,i);
	intToString(1010,str7,i);
	intToString(-1010,str8,i);
	intToString(1001,str9,i);
	intToString(-1001,str10,i);
	intToString(123456789,str11,i);
	intToString(-123456789,str12,i);
	
	printTest("MAX_INT",strcmp(str1,"2147483647"));
	printTest("MIN_INT",strcmp(str2,"-2147483648"));
	printTest("10",strcmp(str3,"10"));
	printTest("-10",strcmp(str4,"-10"));
	printTest("100",strcmp(str5,"100"));
	printTest("-100",strcmp(str6,"-100"));
	printTest("1010",strcmp(str7,"1010"));
	printTest("-1010",strcmp(str8,"-1010"));
	printTest("1001",strcmp(str9,"1001"));
	printTest("-1001",strcmp(str10,"-1001"));
	printTest("123456789",strcmp(str11,"123456789"));
	printTest("-123456789",strcmp(str12,"-123456789"));
	
	printTest("MAX_INT",!(INT_MAX == stringToInt("2147483647",i)));
	printTest("MIN_INT",!(INT_MIN == stringToInt("-2147483648",i)));
	printTest("10",!(10 == stringToInt("10",i)));
	printTest("+10",!(10 == stringToInt("+10",i)));
	printTest("-10",!(-10 == stringToInt("-10",i)));
	printTest("100",!(100 == stringToInt("100",i)));
	printTest("+100",!(100 == stringToInt("+100",i)));
	printTest("-100",!(-100 == stringToInt("-100",i)));
	printTest("1010",!(1010 == stringToInt("1010",i)));
	printTest("+01010",!(1010 == stringToInt("+01010",i)));
	printTest("-01010",!(-1010 == stringToInt("-01010",i)));
	printTest("1001",!(1001 == stringToInt("1001",i)));
	printTest("+1001",!(1001 == stringToInt("+1001",i)));
	printTest("-1001",!(-1001 == stringToInt("-1001",i)));
	printTest("123456789",!(123456789 == stringToInt("123456789",i)));
	printTest("+123456789",!(123456789 == stringToInt("+123456789",i)));
	printTest("-123456789",!(-123456789 == stringToInt("-123456789",i)));
	printTest("Test spaces then 100:",!(100 == stringToInt("    100",i)));
	printTest("Test spaces then 100 then non dig:",!(100 == stringToInt("    100 l",i)));
	printTest("Test spaces then +100 then non dig:",!(100 == stringToInt("    +100 l",i)));
	printTest("Test spaces then -100 then non dig:",!(-100 == stringToInt("    -100 l",i)));


	intToString(85,str13,3);
	intToString(-85,str14,3);
	printTest("10011 base 3 85",strcmp(str13,"10011"));
	printTest("-10011 base 3 -85",strcmp(str14,"-10011"));
	intToString(1270,str15,35);
	intToString(-1270,str16,35);
	printTest("11A base 35 1270",strcmp(str15,"11a"));
	printTest("-11A base 35 -1270",strcmp(str16,"-11a"));
	
	printTest("115 base 8 is 77",!(77 == stringToInt("115",8)));
	printTest("+10014 base 4 is 65",!(65 == stringToInt("+10014",4)));
	printTest("-10ak base 20 is -410",!(-410 == stringToInt("-10ak",20)));

	
	atoiCompare("2147483647");
	atoiCompare("-2147483647");
	atoiCompare("10");
	atoiCompare("-010");
	atoiCompare("1001");
	atoiCompare("-001001");
	
	printTest("19 base 25 is 34",!(34 == stringToInt("19",25)));
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	appearsTwo(arr1,8,arr2,6,arr3,6);
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		
	checkLittleEndian();
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	printf("is big endian? 0 is yes 1 is little:\t%d\n", IS_BIG_ENDIAN);
	return 0;
}
