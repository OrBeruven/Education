/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <math.h>


void FindTwoMissingNumsMath(int arr[], int N)
{
	int sum_h = 0;
	int sum_l = 0;
	
	
	
	int avr = 0;
	
	int sum_smaller = 0;
	int sum_bigger = 0;
	
	int i = 0;
	
	for (i = 0; i < N-2; ++i)
	{
		sum_h += i;
		sum_l += arr[i];
	}
	
	for (; i < N; ++i)
	{
		sum_h += i;
	}
		
	avr = (sum_h - sum_l) / 2;
	
	sum_h = 0;
	sum_l = 0;
	
	for (i = 0; i < N-2; ++i)
	{
		if (arr[i] <= avr)
		{
			sum_smaller += arr[i];
		}
		else
		{
			sum_bigger += arr[i];
		}
		
		if (i <= avr)
		{
			sum_l += i;
		}
		else
		{
			sum_h += i;
		}
	}

	sum_h += i + (i + 1);
	
	
	printf("First num : %d, Second Num %d\n", sum_l - sum_smaller, sum_h - sum_bigger); 
		
}
		
		
void FindTwoMissingNumsXOR(int arr[], int N)		
{
	size_t xor_h = 0;
	size_t xor_l = 0;
	
	size_t mask = 1;
	
	size_t avr = 0;
	
	size_t xor_smaller = 0;
	size_t xor_bigger = 0;
	
	size_t i = 0;
	
	for (i = 0; i < N-2; ++i)
	{
		xor_h ^= i;
		xor_l ^= arr[i];
	}
	
	for (; i < N; ++i)
	{
		xor_h = xor_h ^ i;
	}
	
	avr = (xor_h ^ xor_l);
	
	while (0 == (avr & mask))
	{
		mask <<= 1;
	}
	
	xor_h = 0;
	xor_l = 0;
	
	for (i = 0; i < N-2; ++i)
	{
		if (0 == (arr[i] & mask))
		{
			xor_smaller ^= arr[i];
		}
		else
		{
			xor_bigger ^= arr[i];
		}
		
		if (0 == (i & mask))
		{
			xor_l ^= i;
		}
		else
		{
			xor_h ^= i;
		}
	}

	for(; i < N; ++i)
	{
		if(0 == (i & mask))
		{
			xor_l ^= i;
		}
		else
		{
			xor_h ^= i;
		}
	}

	
	printf("First num : %lu, Second Num %lu\n", xor_smaller ^ xor_l, xor_bigger ^ xor_h); 
	
}
	


int main(void)
{
	int arr[45];
	int i = 0;
	int j = 0;
	int num1 = 12;
	int num2 = 40;
	for(; i < 47; ++i)
	
	{
		if((i != num1) && (i != num2))
		{
			arr[j] = i;
			++j;
		}
	}
	
	FindTwoMissingNumsMath(arr, 47);
	FindTwoMissingNumsXOR(arr, 47);
	
	return 0;
}

