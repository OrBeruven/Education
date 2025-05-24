/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

#define ASCII_SIZE 128


void OneMillChars(char ch)
{
	size_t occur_count = 0;
	static size_t asc_arr[ASCII_SIZE] = {0};
	size_t arr_i = 0;
	size_t i = 0;
	
	if('0' == ch)
	{
		for (i = 0; i < ASCII_SIZE; ++i)
		{
			if (asc_arr[i] > occur_count)
			{
				occur_count = asc_arr[i];
				arr_i = i;
			}
			
			asc_arr[i] = 0;
		}
		
		printf("The maximum occurences of %c is %ld\n", (char)arr_i, occur_count);
		return;
	}
	else
	{
		++asc_arr[(int)ch];
	}
	
	return;
}

size_t NumOfBits(long num)
{
	size_t count = 0;
	
	while (num)
	{
		num = num & (num - 1);
		++count;
	}
	
	return count;
}

int main(void)
{
	long a = 1234556;
	/*char ch = 0;
	
	ch = getchar();
	
	do
	{
		OneMillChars(ch);
		ch = getchar();
	}while (27 != ch);
	*/
	
	printf("%ld is the number of set bits in %ld\n", NumOfBits(a), a);
	return 0;
}
