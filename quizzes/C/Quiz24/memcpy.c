/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include "../../ds/include/utilities.h"

#define ARR_SIZE 9

int MemCpy(const void *src, const void *dest, size_t n)
{
	char *d_run = (char *)dest;
	char *s_run = (char *)src;
	size_t word_size = sizeof(size_t);
	
	--n;
	
	while (0 < n)
	{
		if (n < word_size || (size_t)d_run & (word_size - 1) )
		{
			if (*d_run != *s_run)
			{
				break;
			}
			
			++d_run;
			++s_run;
			--n;
		}
		else
		{
			if (*((size_t *)d_run) != *((size_t *)s_run))
			{
				while (*d_run == *s_run)
				{
					 ++d_run;
					 ++s_run;
				}
				
				break;
			}
			
			d_run += word_size;
			s_run += word_size;
			n -= word_size;
		}
	}
	
	return *s_run - *d_run;
}



int main(void)
{
	char str1[ARR_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
	char str2[ARR_SIZE] =  {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char str3[ARR_SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	
	int arr1[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int arr2[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int arr3[ARR_SIZE] = {0, 1, 3, 3, 4, 5, 6, 7, 8};
	
	RESULTSTATUS(MemCpy(str1, str2, ARR_SIZE), 48);
	RESULTSTATUS(MemCpy(str3, str2, ARR_SIZE), 0);
	
	RESULTSTATUS(MemCpy(arr1, arr2, ARR_SIZE), 0);
	RESULTSTATUS(MemCpy(arr1, arr3, ARR_SIZE), -1);
	
	return 0;
}












