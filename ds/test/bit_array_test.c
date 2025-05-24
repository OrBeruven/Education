/*****************************
	Name : Or Beruven

	Reviewed By : Harel Salhuv
	
	Date Test: 01.02.2023

	Description : c file for bit array_test

*****************************/
#include <stdio.h> /*using - printf*/
#include <string.h> /*using - strcmp*/

#include "../include/bit_array.h"

#define BIT_LENGTH 64

void TestCompareStrings(char *a, char *b)
{
	strcmp(a, b) ? printf("Failed!\n") : printf("Success!\n");
}

void TestCompareBitArrays(bit_array_t a, bit_array_t b)
{
	a == b ? printf("Success!\n") : printf("Failed!\n");
}

void SetOnTest()
{
	bit_array_t num = 3;
	
	/*BitArraySetOn test*/
	printf("BitArraySetOn test : \n");
	num = 3;
	num = BitArraySetOn(num, 3);
	TestCompareBitArrays(num, 11);
	
	num = BitArraySetOn(num, 4);
	TestCompareBitArrays(num, 27);
	num = BitArraySetOn(num, 0);
	TestCompareBitArrays(num, 27);
	printf("\n\n");
}

void SetOffTest()
{
	bit_array_t num = 3;
	
	/*BitArraySetOff test*/
	printf("BitArraySetOff test : \n");
	num = 3;
	num = BitArraySetOff(num, 3);
	TestCompareBitArrays(num, 3);
	
	num = BitArraySetOff(num, 0);
	TestCompareBitArrays(num, 2);
	
	num = -1;
	num = BitArraySetOff(num, 0);
	TestCompareBitArrays(num, -2);
	printf("\n\n");
}
	
void SetValTest()
{
	bit_array_t num = 3;
	
	/*BitArraySetVal test*/
	printf("BitArraySetVal test : \n");
	num = 3;
	num = BitArraySetVal(num, 3, 0);
	TestCompareBitArrays(num, 3);
	
	num = 3;
	num = BitArraySetVal(num, 3, 1);
	TestCompareBitArrays(num, 11);
	
	num = BitArraySetVal(num, 0, 0);
	TestCompareBitArrays(num, 10);
	
	num = -1;
	num = BitArraySetVal(num, 0, 0);
	TestCompareBitArrays(num, -2);
	printf("\n\n");	
}

void SetResetTest()
{
	bit_array_t num = 3;
	
	/*BitArraySetAll test*/
	printf("BitArraySetAll test : \n");
	num = 3;
	num = BitArraySetAll(num);
	TestCompareBitArrays(num, -1);
	
	/*BitArrayResetAll test*/
	printf("BitArrayResetAll test : \n");
	num = BitArrayResetAll(num);
	TestCompareBitArrays(num, 0);
	printf("\n\n");
}

void GetTest()
{
	bit_array_t num = 3;
	
	/*BitArrayGet test*/
	printf("BitArrayGet test : \n");
	num = 3;
	TestCompareBitArrays(BitArrayGet(num, 1), 1);
	TestCompareBitArrays(BitArrayGet(num, 2), 0);
	printf("\n\n");
}

void FlipTest()
{
	bit_array_t num = 3;
	
	/*BitArrayFlip test*/
	printf("BitArrayFlip test : \n");
	num = 3;
	TestCompareBitArrays(BitArrayFlip(num, 1), 1);
	TestCompareBitArrays(BitArrayFlip(num, 2), 7);
	printf("\n\n");
}

void MirrorTest()
{
	bit_array_t num = 3;
	
	/*BitArrayMirror test*/
	printf("BitArrayMirror test : \n");
	num = 1;
	TestCompareBitArrays(BitArrayMirror(num), 0x8000000000000000);
	
	num = -2;
	TestCompareBitArrays(BitArrayMirror(num), 0x7FFFFFFFFFFFFFFF);	
	printf("\n\n");
}

void RotateTest()
{
	bit_array_t num = 3;
	
	/*BitArrayRotate test*/
	printf("BitArrayRotate test : \n");
	num = -2; /*all bits set bside the last one*/
	num = BitArrayRotateLeft(num, 3);
	TestCompareBitArrays(num, 0xFFFFFFFFFFFFFFF7);
	
	num = BitArrayRotateRight(num, 12);
	TestCompareBitArrays(num, 0xFF7FFFFFFFFFFFFF);
	
	num = BitArrayRotateLeft(num, 3);
	TestCompareBitArrays(num, 0xFBFFFFFFFFFFFFFF);
	
	

	num = 1;
	num = BitArrayRotateLeft(num, 3);
	TestCompareBitArrays(num, 8);
	
	num = BitArrayRotateRight(num, 12);
	TestCompareBitArrays(num, 0x80000000000000);
	

	num = 10;
	num = BitArrayRotateLeft(num, 3);
	TestCompareBitArrays(num, 80);

	num = BitArrayRotateRight(num, 7);
	TestCompareBitArrays(num, 0xA000000000000000);
	
	printf("\n\n");
}

void CountOnOffTest()
{
	bit_array_t num = 3;
	
	/*BitArrayCountOn and Off test*/
	printf("BitArrayCount On/Off test : \n");
	num = -2;
	TestCompareBitArrays(BitArrayCountOn(num), 63);
	TestCompareBitArrays(BitArrayCountOff(num), 1);
	num = -4;
	TestCompareBitArrays(BitArrayCountOn(num), 62);
	TestCompareBitArrays(BitArrayCountOff(num), 2);
	
	num = 3;
	TestCompareBitArrays(BitArrayCountOn(num), 2);
	TestCompareBitArrays(BitArrayCountOff(num), 62);
	
	printf("\n\n");
}

void ToStringTest()
{
	bit_array_t num = 3;
	char str[BIT_LENGTH + 1] = {0};
	
	/*BitArrayToString test*/
	printf("BitArrayToString test : \n");
	num = 3;
	BitArrayToString(num, str);
	TestCompareStrings(str, "0000000000000000000000000000000000000000000000000000000000000011");
	
	num = -3;
	BitArrayToString(num, str);
	TestCompareStrings(str, "1111111111111111111111111111111111111111111111111111111111111101");
	printf("\n\n");
}


void MirrorLutTest()
{
	bit_array_t num = 3;
	
	/*BitArrayMirror test*/
	printf("BitArrayMirrorLut test : \n");
	num = 1;
	num = BitArrayMirrorLUT(num);
	TestCompareBitArrays(num, 0x8000000000000000);
	
	num = -2;
	num = BitArrayMirrorLUT(num);
	TestCompareBitArrays(num, 0x7FFFFFFFFFFFFFFF);	
	printf("\n\n");
}

void CountLutTest()
{
	bit_array_t num = 3;
	
	BitArrayCountLutInit();
	
	/*BitArrayCountLut and Off test*/
	printf("BitArrayCount Lut test : \n");
	num = -2;
	TestCompareBitArrays(BitArrayCountLut(num), 63);
	TestCompareBitArrays(BitArrayCountLut(num), BitArrayCountOn(num));
	num = -4;
	TestCompareBitArrays(BitArrayCountLut(num), 62);
	
	num = 3;
	TestCompareBitArrays(BitArrayCountLut(num), 2);
	
	printf("\n\n");
}
	
int main(void)
{	
	SetOnTest();
	
	SetOffTest();
	
	SetValTest();
	
	SetResetTest();
	
	GetTest();
	
	FlipTest();
	
	MirrorTest();
	
	RotateTest();
	
	CountOnOffTest();
	
	ToStringTest();
	
	MirrorLutTest();
	
	CountLutTest();
	
	return 0;
}
