#include <stdio.h>

int CountBits(unsigned char num)
{
	int count = 0;
	
	while (0 < num)
	{
		count += (num & 1) && ((num >> 1) & 1);
		num >>= 1;
	}
	
	return count;
}

void SwapA(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
	
	return;
}

void SwapB(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;

	return;
}


void SwapC(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	
	return;
}

int NumOfBits(long num)
{
	int result = 0;
	while (num)
	{
		num = num & (num - 1);
		++result;
	}
	
	return result;
}

int main(void)
{
	int a = 10;
	int b = 5;
	unsigned char ch = 118;
	long num = 1354;
	
	printf("The number of set bit is %d is %d\n", ch, CountBits(ch));
	
	printf("Before a = %d, b = %d.\n", a, b);
	
	SwapA(&a, &b);
	printf("After SwapA a = %d, b = %d\n", a, b);
	
	SwapB(&a, &b);
	printf("After SwapB a = %d, b = %d\n", a, b);
	
	SwapC(&a, &b);
	printf("After SwapC a = %d, b = %d\n", a, b);
	
	printf("The number of set bits in %ld is %d\n", num, NumOfBits(num));

	return 0;
}
	
