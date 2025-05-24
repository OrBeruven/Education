/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

void SortArr(int arr[], size_t size);
void SwapVal(int *a, int *b);
static void PrintArr(int arr[], size_t size);

void SortArr(int arr[], size_t size)
{
	size_t i = 0;
	size_t end = size - 1;
	
	for (i = 0; i <= end; ++i)
	{
		while (1 == arr[i] && i != end)
		{
			SwapVal(&arr[i], &arr[end]);
			--end;
		}
	}
}

void SwapVal(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

static void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n");
}

int main(void)
{
	int arr[10] = {0, 1, 1, 0, 1, 0, 1, 0, 1, 0};
	int a1[] = {1, 1, 0, 0, 1, 0, 1, 0, 0 ,0 ,0, 0, 1, 0, 1, 1, 1 ,1 ,1 ,1 ,1 , 0, 0, 1, 0, 0, 0, 1};
	size_t len = sizeof(a1) / sizeof(int);
	
	PrintArr(arr, 10);
	SortArr(arr, 10);
	PrintArr(arr, 10);
	
	printf("\n");
	PrintArr(a1, len);
	SortArr(a1, len);
	PrintArr(a1, len);
	return 0;
}
