/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

#define SUCCESS 1
#define FAILURE 0

int TraverseArr(int arr[], size_t size, int index)
{
	if (index == (int)size - 1)
	{
		return SUCCESS;
	}
	else if (index >= (int)size || index < 0)
	{
		return FAILURE;
	}
	
	if (SUCCESS == TraverseArr(arr, size, index + arr[index]))
	{
		return SUCCESS;
	}
	
	if (SUCCESS == TraverseArr(arr, size, index - arr[index]))
	{
		return SUCCESS;
	}
	
	return FAILURE;
}
	
int ArrJump(int a[], size_t len, int i)
{
	if ((len <= (size_t)i) || (i < (int)0))
	{
		return 0;
	}
	
	if (a[i] <= 0)
	{
		return 0;
	}
	
	if (len - 1 == (size_t)i)
	{
		return 1;
	}
	
	a[i] *= -1;
	
	return ArrJump(a, len, i + a[i]) + ArrJump(a, len, i - a[i]);
}


int main(void)
{
	int arr[9] = {2, 4, 1, 6, 4, 2, 4, 3, 5};
	int arr2[9] = {2, 4, 1, 5, 10, 2, 4, 3, 5};
	int arr3[4] = {2, 4, 2, 5};
	
	if (SUCCESS == 	ArrJump(arr, 9, 0))
	{
		printf("SUCCESS\n");
	}
	else
	{
		printf("FAILURE\n");
	}
	
	if (SUCCESS == 	ArrJump(arr2, 9, 0))
	{
		printf("SUCCESS\n");
	}
	else
	{
		printf("FAILURE\n");
	}
	
	if (SUCCESS == 	ArrJump(arr3, 4, 0))
	{
		printf("SUCCESS\n");
	}
	else
	{
		printf("FAILURE\n");
	}
	return 0;
}
