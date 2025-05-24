/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <stddef.h>

#define BASE 10
#define PRINT printf("\033[1;32msuccess\n\033[0m") : printf("\033[1;31mfail\n\033[0m")

static size_t MulDigitNum(size_t num);

size_t DigitSum(size_t num)
{
	if (0 == num)
	{
		return 0;
	}
	
	return (num % BASE) + DigitSum(num / BASE);
}

size_t FlipNum(size_t num)
{
	if (0 == num)
	{
		return 0;
	}
	
	return ((num % BASE) * (DigitNum(num))) + FlipNum(num / BASE);
}

static size_t MulDigitNum(size_t num)
{
	if (0 == num / 10)
	{
		return 1;
	}
	
	return 10 * DigitNum(num / BASE);
}


int main(void)
{
	printf("The sum of 12223 = %lu\n", DigitSum(12223));
	printf("The sum of 12223 = %lu\n", FlipNum(12223));
	
	printf("DigitSum Test:\n");

	6 == DigitSum(123) ? PRINT;
	17 == DigitSum(12347) ? PRINT;
	1 == DigitSum(1) ? PRINT;
	0 == DigitSum(0) ?PRINT;
	
	printf("FlipNum Test:\n");
	
	123 == FlipNum(321) ? PRINT;
	2 == FlipNum(2) ? PRINT;
	789789 == FlipNum(987987) ? PRINT;
	123456 == FlipNum(654321) ? PRINT;
	314159 == FlipNum(951413) ? PRINT;
	
	return 0;
}
