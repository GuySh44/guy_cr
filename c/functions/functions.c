#include"functions.h"


static void printA()
{
	printf("A-pressed\n");
}

static void printT()
{
	printf("T-pressed\n");
}

static void exitESC()
{
	system("stty icanon echo");
	exit(0);
}

static void emptyFunc(){}

void ifImplement()
{
	char ch;
	system("stty -icanon -echo");
	while(scanf(" %c",&ch))
	{
		if(ch == 'A' || ch == 'a')
		{
			printf("A-pressed\n");	
		}
		if(ch == 'T' || ch == 't')
		{
			printf("T-pressed\n");	
		}
		if(ch == ESC)
		{
			system("stty icanon echo");
			exit(0);
		}
	}
}

void switchImplement()
{
	char ch;
	system("stty -icanon -echo");
	while(scanf(" %c",&ch))
	{
		switch(ch)
		{
			case ('A'):
				printf("A-pressed\n");		
				break;
			case ('a'):
				printf("A-pressed\n");		
				break;
			case ('T'):
				printf("T-pressed\n");		
				break;
			case ('t'):
				printf("T-pressed\n");		
				break;
			case (ESC):
				system("stty icanon echo");
				exit(0);
		}
	}
}

void lutImplement()
{
	char ch;
	int i = 0;
	typedef void (*f_p_array[256])();
	f_p_array arr;
	for(; i < 256; i++)
	{
		arr[i] = &emptyFunc;
	}
	arr['a'] = &printA;
	arr['A'] = &printA;
	arr['t'] = &printT;
	arr['T'] = &printT;
	arr[ESC] = &exitESC;
	system("stty -icanon -echo");
	while(scanf(" %c",&ch))
	{
		arr[(unsigned)ch]();	
	}
}







