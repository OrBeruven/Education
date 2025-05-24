/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

size_t NumOfRotations(int arr[], size_t size)
{
	size_t min = 0;
	size_t max = 0;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] > arr[max])
		{
			max = i;
		}
		else if (arr[i] < arr[min])
		{
			min = i;
		}
	}
	
	if ((0 == min && size-1 == max) || (0 == max && size-1 == min))
	{
		return 0;
	}
	
	return min > max ? size - min : size - max;
}


size_t BinNumOfRotations(int arr[], size_t size)
{
	size_t l = 0;
	size_t r = size-1;
	size_t mid = (l + r) / 2;
	
	if (2 >= size)
	{
		return 0;
	}
	
	while (arr[r] < arr[l])
	{
		if (arr[mid] > arr[l])
		{
			l = mid;
			mid = (l + r) / 2;
		}
		else
		{
			r = mid;
			mid = (l + r) / 2;
		}
	}
	
	
	return size - (r + 1);
}
	
	
	
	
	

int main(void)
{
	int arr[10] = {4, 5, 6, 7, 8, 9, 10, 1, 2, 3};
	int arr2[10] = {3, 2, 1, 10, 9, 8, 7, 6, 5, 4};
	int arr3[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr4[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 1};
	int arr5[10] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int arr6[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	
	printf("NumOfRotations = %ld should be 3\n", NumOfRotations(arr, (size_t)10));
	printf("NumOfRotations = %ld should be 7\n", NumOfRotations(arr2, (size_t)10));
	printf("NumOfRotations = %ld should be 0\n", NumOfRotations(arr3, (size_t)10));
	printf("NumOfRotations = %ld should be 1\n", NumOfRotations(arr4, (size_t)10));
	printf("NumOfRotations = %ld should be 9\n", NumOfRotations(arr5, (size_t)10));
	printf("NumOfRotations = %ld should be 0\n", NumOfRotations(arr6, (size_t)10));
	
	printf("\n\n");
	
	printf("NumOfRotations = %ld should be 3\n", BinNumOfRotations(arr, 10));
	/*printf("NumOfRotations = %ld should be 7\n", BinNumOfRotations(arr2, (size_t)10));*/
	printf("NumOfRotations = %ld should be 0\n", BinNumOfRotations(arr3, 10));
	printf("NumOfRotations = %ld should be 1\n", BinNumOfRotations(arr4, 10));
	printf("NumOfRotations = %ld should be 9\n", BinNumOfRotations(arr5, 10));
	/*printf("NumOfRotations = %ld should be 0\n", BinNumOfRotations(arr6, (size_t)10));*/
	return 0;
}
