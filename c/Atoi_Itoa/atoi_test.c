/*****************************
	Name : Or Beruven

	Reviewed By : Neviu Mamu

	Date Test: 27.1.2023

	Description : c file for atoi/itoa

*****************************/

#include <stdio.h> /*using - printf*/
#include <stdlib.h> /*using - atoi*/
#include <string.h> /*using - strcpy*/
#include "atoi.h"

#define BUFF_SIZE 64
#define LIL_BUFF 8
#define ASCII_SIZE 128

#define IS_LITTLE_ENDIAN ((*(size_t *)"\0\xff" > 0x100))

/*#define ISLITTLE (*(char *) & (int)1)*/

static void TestAtoiItoa();
static void TestAscii();

int main(void)
{
	TestAtoiItoa();
	
	TestAscii();
	
	
	if(!IsLittleEnd())
	{
		printf("Little Endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}
	
	if(IS_LITTLE_ENDIAN)
	{
		printf("Little Endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}
	
	return 0;
}

static void TestAscii()
{
	char arr[LIL_BUFF] = "abaaacdE";
	char arr2[LIL_BUFF] = "abEaacD";
	char arr3[LIL_BUFF] = "ahkp";
	
	ThreeArrays(arr, arr2, arr3);
}

static void TestAtoiItoa()
{
	char buffer[BUFF_SIZE] = {"723d"};
	char test[45]="1101010000110101";
	int a = 54325;
	char library_str[20];
	
	/*test for atoi*/
	printf("The answer of %s in base 2 - system atoi= %d, my atoi = %d\n", buffer, atoi(buffer), Atoi(buffer));
	strcpy(buffer, "845165");
	printf("The answer of %s in base 2 - system atoi= %d, my atoi = %d\n", buffer, atoi(buffer), Atoi(buffer));
	strcpy(buffer, "Abc");
	printf("The answer of %s in base 2 - system atoi= %d, my atoi = %d\n", buffer, atoi(buffer), Atoi(buffer));
	strcpy(buffer, "-845165");
	printf("The answer of %s in base 2 - system atoi= %d, my atoi = %d\n", buffer, atoi(buffer), Atoi(buffer));
	

	/*test for AtoiForAnyBase */
	printf("\nTests for AtoiForAnyBase :\n");
	printf("should be 54325 = %d\n", AtoiForAnyBase(test,2));
	test[3] = '2';
	printf("should be 6 = %d\n", AtoiForAnyBase(test,2));
	strcpy(buffer, "-8455");
	printf("The answer of %s in base 23 should be -99572 %d\n", buffer, AtoiForAnyBase(buffer, 23));
	strcpy(buffer , "9BP");
	printf("The answer of %s in base 30 should be 8455 %d\n", buffer, AtoiForAnyBase(buffer, 30));
	
	
	printf("\n\n");
	
	
	/*test for ItoaForAnyBase */
	printf("Tests for ItoaForAnyBase :\n");
	ItoaForAnyBase(a, library_str,2);
	printf("should be 1101010000110101 = %s\n", library_str);
	
	a = 52;
	ItoaForAnyBase(a, library_str, 8);
	printf("should be 64 = %s\n", library_str);
	
	a = 19851;
	ItoaForAnyBase(a, library_str, 29);
	printf("should be NHF = %s\n", library_str);
	
	printf("\n\n");

	
	
	
	
	return;
}











