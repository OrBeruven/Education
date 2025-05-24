/*****************************
	Name : Or Beruven

	Reviewed By : Noam Gazit

	Date Test :	23.01.2023

	Description : c file for word_boundary

*****************************/

#include <stdio.h> /*using - printf*/
#include <string.h> /*using - memcpy, memmove, memset (for tests)*/

#include "word_boundary.h"

#define ARR_SIZE 9

void PrintArr(void *ar)
{
	unsigned char *arr = ar;
	int i = 0;	
	for (i = 0; ARR_SIZE > i; ++i)
	{
		printf("%c", *(arr + i));
	}
	printf("\n");
}

void PrintIntArr(void *ar)
{
	int *arr = ar;
	int i = 0;	
	for (i = 0; ARR_SIZE > i; ++i)
	{
		printf("%d,", *(arr + i));
	}
	printf("\n");
}


int main(void)
{
	char str[ARR_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
	char to_cpy[ARR_SIZE] =  {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'};
	char mem_cpy[ARR_SIZE] = {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'};
	
	int arr[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int my_cpy_arr[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int mem_cpy_arr[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int i = 0;
	
	/*test for char array*/
	/*
	MemSetWord(str + 1, 'b', ARR_SIZE - 4);*/
	printf("check char arr\nstr = ");
	PrintArr(str);
	MemCpy(to_cpy, str, ARR_SIZE);
	memcpy(mem_cpy, str, ARR_SIZE);
	
	MemMove(to_cpy, to_cpy + 2, 4);
	memmove(mem_cpy, mem_cpy + 2, 4);
	
	printf("\n");
	printf("to cpy = ");
	PrintArr(to_cpy);
	
	printf("\n");
	printf("mem cpy = ");
	PrintArr(mem_cpy);
	
	
	
	/*test for int arr*/
	for(i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = i;
	}
	printf("\n\n\nCheck int arr \n");
	PrintIntArr(arr);
	
	/*MemSetWord(my_cpy_arr, 1, ARR_SIZE * 4);
	memset(mem_cpy_arr, 1, ARR_SIZE* 4);
	*/
	
	/*MemCpy(my_cpy_arr, arr, ARR_SIZE * 4);
	memcpy(mem_cpy_arr, arr, ARR_SIZE * 4);*/
	
	MemMove(my_cpy_arr, my_cpy_arr + 2, 4 * 4);
	memmove(mem_cpy_arr, mem_cpy_arr + 2, 4 * 4);
	printf("\nMy mem = ");
	PrintIntArr(my_cpy_arr);
	
	printf("\nmem cpy = ");
	PrintIntArr(mem_cpy_arr);
	
	
	
	
	
	
	return 0;
}
