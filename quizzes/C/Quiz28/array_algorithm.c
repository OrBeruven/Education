/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

int IsInArr(char arr[], size_t size, char ch);
void ShiftN(char arr[], size_t size, int shift);
static void ReverseArr(char arr[], size_t size);

int IsInArr(char arr[], size_t size, char ch)
{
	char lut[256] = {0};
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		lut[arr[i]] = 1;
	}
	
	return lut[ch];
}

int IsInArr2(char arr[], size_t size, char ch)
{
	size_t i = 0;
	size_t count = 0;
	
	for (i = 0; i < size; ++i)
	{
		 count += (arr[i] == ch);
	}
	
	return !!count; /*nirmul*/
}

void ShiftN(char arr[], size_t size, int shift)
{
	ReverseArr(arr, shift);
	ReverseArr(arr + shift, size - shift);
	ReverseArr(arr, size);
}


static void ReverseArr(char arr[], size_t size)
{
	size_t i = 0;
	char temp = 0;
	
	for (i = 0; i < size / 2; ++i)
	{
		temp = arr[i];
		arr[i] = arr[size-i-1];
		arr[size-i-1] = temp;
	}
}

int main()
{
	char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
	size_t i = 0;
	
	ShiftN(arr, 7, 5);
	
	for (i = 0; i < 7; ++i)
	{
		printf("%c, ", arr[i]);
	}
	
	printf("\n");

	return 0;
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
