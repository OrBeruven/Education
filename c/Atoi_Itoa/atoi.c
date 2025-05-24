/*****************************
	Name : Or Beruven

	Reviewed By : Neviu Mamu

	Date Test: 27.1.2023

	Description : c file for atoi/itoa

*****************************/

#include <stdio.h> /*using - NULL, size_t (could add sttdef), printf*/
#include <assert.h> /*using assert*/
#include "atoi.h"

#define BASE10 10
#define ASCII_SIZE 128

typedef enum num_type {ISPOS, ISNEG, ISZERO} num_type_t;

static void RevStr(char *buffer, size_t len)
{
	char swap_temp = 0;
	size_t i = 0;
	
	assert(NULL != buffer);
	
	for (i = 0; i < len; ++i)
	{
		swap_temp = buffer[i];
		buffer[i] = buffer[len - 1];
		buffer[len-1] = swap_temp;
		
		--len;
	}
}

char *Itoa(int num, char *buffer)
{
	int flag = ISPOS;
	size_t i = 0;
	
	assert(NULL != buffer);
	
	if(0 > num)
	{
		num *= -1;
		flag = ISNEG;
	}
	else if(0 == num)
	{
		buffer[i] = '0';
		buffer[++i] = '\0';
		return buffer;
	}
	
	while (num > 0)
	{
		buffer[i] = (char)((num % 10) + 48);
		num /= BASE10;
		++i;
	}
	
	if(flag == ISNEG)
	{
		buffer[i] = '-';
		++i;
	}
	
	RevStr(buffer, i);
	buffer[i] = '\0';
	
	return buffer;
}

int Atoi(const char *nptr)
{
	int to_ret = 0;
	int flag = ISPOS;
	
	assert(NULL != nptr);
	
	if('-' == *nptr)
	{
		++nptr;
		flag = ISNEG;
	}
	
	while('\0' != *nptr && ('0' <= *nptr && *nptr <= '9'))
	{
		to_ret = (to_ret * BASE10) + (*nptr - 48);
		++nptr;
	}
	
	return flag == ISNEG ? -to_ret : to_ret;
}

char *ItoaForAnyBase(int num, char *buffer, int base)
{
	int flag = ISPOS;
	size_t i = 0;
	int reminder = 0;
	
	assert(NULL != buffer);
	
	if(0 > num)
	{
		num *= -1;
		flag = ISNEG;
	}
	else if(0 == num)
	{
		buffer[i] = '0';
		buffer[++i] = '\0';
		return buffer;
	}
	
	while (num > 0)
	{
		reminder = num % base;
		
		/*in bases 16 and 32 we're dealing with numbers*/
		if (9 < reminder)
		{
			buffer[i] = (reminder -10) + 'a';
		}
		else
		{
			buffer[i] = reminder +'0';
		}
		
		num /= base;
		++i;
	}
	
	if(flag == ISNEG)
	{
		buffer[i] = '-';
		++i;
	}
	
	RevStr(buffer, i);
	buffer[i] = '\0';
	
	return buffer;
}

int AtoiForAnyBase(const char *nptr, int base)
{
	int to_ret = 0;
	int is_base = 0;
	int flag = ISPOS;
	
	assert(NULL != nptr);
	
	if('-' == *nptr)
	{
		flag = ISNEG;
		++nptr;
	}
	
	while('\0' != *nptr)
	{
		/*if it's an integer*/
		if('0' <= *nptr && *nptr <= '9')
		{
			is_base = (*nptr - 48);
			if(is_base >= base)
			{
				break;
			}
			
			to_ret = (to_ret * base) + is_base;
		}
		else if('a' <= *nptr && *nptr <= 'z')
		{
			is_base = ((*nptr - 'a') + 10);
			if(is_base >= base)
			{
				break;
			}
			to_ret = (to_ret * base) + is_base;
		}
		else if('A' <= *nptr && *nptr <= 'Z')
		{
			is_base = ((*nptr - 'A') + 10);
			if(is_base >= base)
			{
				break;
			}
			to_ret = (to_ret * base) + is_base;
		}
		else
		{
			break;
		}
		++nptr;
	}
	
	return flag == ISNEG ? -to_ret : to_ret;
}

void ThreeArrays(char *arr, char *arr2, char *arr3)
{
	char ascii_table[ASCII_SIZE] = {0};
	size_t i = 0;
	
	assert(NULL != arr);
	assert(NULL != arr2);
	assert(NULL != arr3);
	
	while ('\0' != *arr)
	{
		if(ascii_table[(int)*arr] == 0)
		{
			++ascii_table[(int)*arr];
		}
		++arr;
	}

	while ('\0' != *arr2)
	{
		++ascii_table[(int)*arr2];
		++arr2;
	}
	
	while ('\0' != *arr3)
	{
		ascii_table[(int)*arr3] = 0;
		++arr3;
	}
	
	for(i = 0; ASCII_SIZE > i; ++i)
	{
		if(ascii_table[i] > 1)
		{
			printf("%c ", (char)i);
		}
	}
	printf("\n");
	return;
}

/*returns 1 if big, 0 if little */
int IsLittleEnd()
{
	int num = 1;
	
	return *(char *)&num == 1 ? 0 : 1;
}












