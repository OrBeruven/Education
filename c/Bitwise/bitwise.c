/******************

Coded by : Or Beruven

Reviewed by : Yotam Adler

*******************/

#include <stdio.h>

enum flag {FALSE, TRUE};

long Pow2(unsigned int x, unsigned int y)
{	
	return x << y;
}

int Ex2Loop(unsigned int n)
{
	unsigned int is_two = 1 << 1;
	
	while ((0 < is_two) && (0 < n))
	{
		is_two = is_two >> (1 & n);
		n = n >> 1;
	}
	
	return (1 & is_two);
}

int Ex2WithoutLoop(unsigned int n)
{
	return !(n & (n - 1));
}


int Ex3AddOne(int num)
{
	unsigned int digit = 1;
	
	while (num & digit)
	{
		num = num ^ digit;	/*	num = 0101	0100  0110		*/
		digit = digit << 1;	/* 	m   = 0001 		*/
	}
	
	num = num ^ digit;
	
	return num;	
}

unsigned int Ex9AddOne(unsigned int *num)
{
	unsigned int m = 1;
	
	while (*num & m)
	{
		*num = *num ^ m;	/*	num = 0101	0100  0110		*/
		m = m << 1;	/* 	m   = 0001 		*/
	}
	
	*num = *num ^ m;
	
	return *num;	
}

void Ex4BitsOn(int arr[], int size)
{
	int count = 0;
	int temp = 0;
	int is_three = 1 << 1; /*setting variable to two and make it a counter for 7*/
	is_three = is_three | 1;
	is_three <<= 1;
	is_three = is_three | 1;
	
	while (count < size)
	{
		temp = arr[count];
		
		while ((0 < temp) && (1 & is_three))
		{
			is_three >>= (1 & temp);
			temp >>= 1;
		}
		
		if (!(0 | is_three) && !temp)
		{
			printf("%d has 3 bits on \n", arr[count]);
		}
		count = Ex3AddOne(count);
		
		is_three = 1 << 1;
		is_three |= 1;
		is_three <<= 1;
		is_three |= 1;
	}		
}
/*
num = 1110	0111	0011	0001
rev = 1110	11100	11101	111010	111011	1110110	1110111		 

num = 1001	0100	0010	0001	
rev = 1001	10010	10010	100100	100100	1001000	1001001*/	

int ByteRverse(int num)
{
	int rev_num = 0;
	while (num)
	{
		rev_num <<= 1;	
		rev_num |= 1 & num;
		num >>= 1;
	}
	return rev_num;
}

unsigned char ByteRevB(unsigned char src)
{
	return (((0x80 & src) >> 7) | ((0x40 & src) >> 5) | ((0x20 & src) >> 3) | ((0x10 & src) >> 1) |
			((0x08 & src) << 1) | ((0x04 & src) << 3) | ((0x02 & src) << 5) | ((0x01 & src) << 7));
}

/*	00100101 = 10100100 
	37 = 164
	
	11010100 = 00101011
	212 = 43
*/

int Ex6A(unsigned char src)
{	
	return (((src >> 1) & 1) && ((src >> 5) & 1)) ? 1 : 0;
	/*100010	10001   & 1 = true	1 & 1 = true  return 1*/
}

int Ex6B(unsigned char src)
{
	return (((src >> 1) & 1) || ((src >> 5) & 1)) ? 1 : 0;
}

unsigned char Ex6C(unsigned char src)
{
	/*unsigned char place_3 = src >> 2;
	unsigned char place_5 = src >> 4;
	
	src >> 4 */
	unsigned char dst = 0;
	dst = (((0x80 & src) >> 0) |
		((0x40 & src) >> 0) |
		((0x20 & src) >> 0) |
		((0x10 & src) >> 3) |
		((0x08 & src) << 0) |
		((0x04 & src) << 0) |
		((0x02 & src) << 3) |
		((0x01 & src) << 0)
	);
	
	/*return ((x & 4) << 2) | ((x & 16) >> 2) */
	/*return ((x & 235) + ((x & 4) << 2) + ((x & 16) >> 2));*/
	
	/*
	11101 ==== 10111
	
	1 | 
	
	
	29 = 	00011101
			0000111  
			
			10010110
			    1001  
		  	01110100  
	116 = 	01110100
	*/
	
	return dst;
}

int Ex7(unsigned int num)
{
	return num >>= 0x04, num <<= 0x04;
	
	/*return ( (x >> 4) << 4);*/
}

void Ex8(unsigned int *num1, unsigned int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num2 ^ *num1;
	*num1 = *num1 ^ *num2;
	return;
}

unsigned int Ex9A(int num)
{
	unsigned int count = 0;
	
	while (0 < num)
	{
		(1 & num) && Ex9AddOne(&count);
		
		num >>= 1;
	}
		
	return count;
}

int Ex9B(int num)
{
	num = (0x55555555 & num) + (0x55555555 & (num >>  1)); /*mask for : 01010101 */
	num = (0x33333333 & num) + (0x33333333 & (num >>  2)); /*mask for : 00110011 */
	num = (0x0f0f0f0f & num) + (0x0f0f0f0f & (num >>  4)); /*mask for : 00001111 */
	num = (0x00ff00ff & num) + (0x00ff00ff & (num >>  8)); /*mask for : 0000000011111111 */
	return num;
}

void Ex10(float num)
{
	int i = 0;
	unsigned int *ptr = (unsigned int *)&num;
	for (i = 31; 0 < i; --i)
	{
		printf("%d", (*ptr >> i) & 1);
	}	
	/*
	for (i = 22; 0 < i; --i)
	{
		printf("%d", (*ptr >> i) & 1);
	}*/
		
	return;
}

int fiveorsevemn(int num)
{
	/*num = !(0x02 & num)*/ 
	return num ^ 2;
}

int main(void)
{
	int num = 7;
	float fnum = 18.75;
	/*int temp = ;*/
	unsigned char ch = 128;
	/*int arr[3] = {14, 1065, 1064};*/
	/*printf("%ld\n", Pow2(0x02, 0x02));*/
	/*printf("%d answer = %d\n", temp, Ex2Loop(temp));*/
	/*printf("%d answer = %d\n", temp, Ex2WithoutLoop(temp));*/
	/*printf("%d answer = %d\n", temp, Ex3AddOne(temp));*/
	/*Ex4BitsOn(arr, 3);*/
	printf("Answer in rev %d\n", ByteRverse(ch));
	/*printf("Answer in revB %d\n", ByteRevB(ch));*/
	/*if (Ex6B(ch))
	{
		printf("%d is true\n", ch);
	}
	else
	{
		printf("%d is false\n", ch);
	}*/
	
	/*printf("%d\n", Ex6C(ch));*/
	
	/*printf("The closest divide to 16 from %u is %u\n", num, Ex7(num));*/
	
	/*printf("Before swap num1 = %u, num2 = %u\n", num1, num2);
	Ex8(&num1, &num2);
	printf("After swap num1 = %u, num2 = %u\n", num1, num2);	
	*/
	
	/*printf("There are %u bits set on %d\n", Ex9A(num), num);*/
	
/*	printf("The number of set bits in %d is = %d\n", num, Ex9B(num));
	
	
	printf("The number %d after swap %d\n", num, fiveorsevemn(num));*/
	
	Ex10(fnum);
	printf("\n");
	return 0;
}	





























