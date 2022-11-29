#include"atoi_itoa.h"
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include"../../my_tests/utils.h"

int main()
{
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
	
	intToString(INT_MAX,str1);
	intToString(INT_MIN,str2);
	intToString(10,str3);
	intToString(-10,str4);
	intToString(100,str5);
	intToString(-100,str6);
	intToString(1010,str7);
	intToString(-1010,str8);
	intToString(1001,str9);
	intToString(-1001,str10);
	intToString(123456789,str11);
	intToString(-123456789,str12);
	
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
	
	printTest("MAX_INT",!(INT_MAX == stringToInt("2147483647")));
	printTest("MIN_INT",!(INT_MIN == stringToInt("-2147483648")));
	printTest("10",!(10 == stringToInt("10")));
	printTest("+10",!(10 == stringToInt("+10")));
	printTest("-10",!(-10 == stringToInt("-10")));
	printTest("100",!(100 == stringToInt("100")));
	printTest("+100",!(100 == stringToInt("+100")));
	printTest("-100",!(-100 == stringToInt("-100")));
	printTest("1010",!(1010 == stringToInt("1010")));
	printTest("+1010",!(1010 == stringToInt("+1010")));
	printTest("-1010",!(-1010 == stringToInt("-1010")));
	printTest("1001",!(1001 == stringToInt("1001")));
	printTest("+1001",!(1001 == stringToInt("+1001")));
	printTest("-1001",!(-1001 == stringToInt("-1001")));
	printTest("123456789",!(123456789 == stringToInt("123456789")));
	printTest("+123456789",!(123456789 == stringToInt("+123456789")));
	printTest("-123456789",!(-123456789 == stringToInt("-123456789")));
	printTest("Test spaces then 100:",!(100 == stringToInt("    100")));
	printTest("Test spaces then 100 then non dig:",!(100 == stringToInt("    100 l")));
	printTest("Test spaces then +100 then non dig:",!(100 == stringToInt("    +100 l")));
	printTest("Test spaces then -100 then non dig:",!(-100 == stringToInt("    -100 l")));

	return 0;
}
