/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

int IsNumInArrOranWay(int arr[], size_t size, int num)
{
	size_t i = 0;
	int sum = 0;
	
	for (i = 0; i < size; ++i)
	{
		arr[i] -= num;
		arr[i] = !arr[i];
		sum += arr[i];
	}
	
	return (0 < sum);
}

int IsNumInArrAvriWay(int arr[], size_t size, int num)
{
	size_t i = 0;
    long sum = 1;
    
    for(i = 0; size > i; ++i)
    {
        arr[i] = arr[i] - num;
        sum *= arr[i];
    }
    
    if (sum == 0)
    {
    	return 1;
    }
    else
    {
    	return 0;
    }
}
	
	
int IsInArray(int arr[], size_t size, int num)
{
	int lut[1000] = {0};
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		++lut[arr[i]];
	}
	
	if (0 < lut[num])
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

int IsInArray2(int arr[], size_t size, int num)
{
	size_t i = 0;
	
	while (i < size && num != arr[i])
	{
		++i;
	}
	
	if (i < size)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
	
int main(void)
{
	int arr[7] = {0, 1, 3, 3, 3, 7, 10};
	int arr2[7] = {0, 1, 3, 3, 3, 7, 10};
	int arr3[7] = {0, 1, 3, 3, 3, 7, 10};	 
	int arr4[7] = {0, 1, 3, 3, 3, 7, 10};
	
	IsInArray(arr, 7, 3) ? printf("In Array\n") : printf("Isnt in array\n");
	IsInArray2(arr2, 7, 3) ? printf("In Array\n") : printf("Isnt in array\n");
	IsNumInArrOranWay(arr3, 7, 3) ? printf("In Array\n") : printf("Isnt in array\n");
	IsNumInArrAvriWay(arr4, 7, 3) ? printf("In Array\n") : printf("Isnt in array\n");
	
	return 0;
}
