/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>


long *SumIntPairsToLongs(int ints[], size_t size)
{
	long *long_ptr = (long *)ints;
	size_t i = 0;

	for (i = 0; i < size; i += 2)
	{
		long_ptr[i/2] = (long)ints[i] + (long)ints[i+1];
	}
	
	return long_ptr;
}




int main(void)
{
	size_t size = 6;
	int ints[6] = {1, 2147483647, 456, -3, 8, 12};
	long *sum = NULL;
	size_t i = 0;
	
	sum = SumIntPairsToLongs(ints, size);
	
	for (i = 0; i < size/2; ++i)
	{
		printf("%ld, ", sum[i]);
	}
	
	
	
	
	return 0;
}
























