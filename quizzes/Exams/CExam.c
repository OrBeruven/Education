/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define DEC_BASE 10;


/*Question 16*/
void foo()
{
    char *s1 = "hello";
    char s2[] = "hello";
    char *s3 = s1;
    printf("%lu %lu %lu %lu \n", sizeof(s1), sizeof(s2), strlen(s1), strlen(s2));
    s3[0] = 'H';
    printf("%s \n", s3);
}
/*Question 17*/
void foo2()
{
    size_t array[] = {0, 1, 2, 3, 4, 5};
    size_t val = 3;
    printf("%lu \n", val[array]);
}

/*Question 21*/
struct S1
{
    int *i;
    char c;
    short s;
    int *j;
};

/*Question 22*/ 
struct S2
{
    unsigned int i : 2;
    unsigned char c : 1;
    unsigned short s : 3;
    int *j;
    unsigned char x : 2;
};

/*Question 23*/
union
{
    char array[7];
    int i;
    short s;
} jack;


int FlipDigitsInNum(int num)
{
	int is_negative = 0;
	int result = 0;
	
	if (0 > num)
	{
		is_negative = 1;
		num = num * -1;
	}
	
	while (num)
	{
		result *= DEC_BASE;
		result += num % DEC_BASE;
		num /= DEC_BASE;
	}
	
	return is_negative ? -result : result;
}
void FlipDigitsTest(int num, int num_rev)
{
	FlipDigitsInNum(num) == num_rev ? printf("Success\n") : printf("Failure");
}


char MirrorByte(unsigned char byte)
{
	unsigned char mirror_byte = 0;
	
	while (byte)
	{
		mirror_byte <<= 1;
		mirror_byte |= byte & 1;
		byte >>= 1;
	}
	
	return mirror_byte;
}

void MirrorByteTest(void)
{
	MirrorByte((char)129) == (char)129 ? printf("Success\n") : printf("Failure");
	MirrorByte((char)255) == (char)255 ? printf("Success\n") : printf("Failure");
	MirrorByte((char)240) == (char)15 ? printf("Success\n") : printf("Failure");
}


int FlipBit(int value, unsigned int n)
{
	return value ^ (1 << n);
}

void FlipBitTest(void)
{
	FlipBit(88, 2) == 92 ? printf("Success\n") : printf("Failure");
	FlipBit(88, 3) == 80 ? printf("Success\n") : printf("Failure");
}
	
	
size_t CountBitsOn(char byte)
{
	size_t counter = 0;
	
	while (byte)
	{
		byte = byte & (byte - 1);	
		++counter;
	}
	
	return counter;
}

void CountBitsTest(void)
{
	CountBitsOn(1) == 1 ? printf("Success\n") : printf("Failure");
	CountBitsOn(2) == 1 ? printf("Success\n") : printf("Failure");
	CountBitsOn(3) == 2 ? printf("Success\n") : printf("Failure");
	CountBitsOn(0) == 0 ? printf("Success\n") : printf("Failure");
	CountBitsOn(1) == 1 ? printf("Success\n") : printf("Failure");
	CountBitsOn(90) == 4 ? printf("Success\n") : printf("Failure");
}
	
void PrintBit(char num)
{
	int i = 0;
	num = MirrorByte(num);
	for (i = 0; i < 8; ++i)
	{
		printf("%d", num & 1);
		num >>= 1;
	}
	printf("\n");
}

char RotateLeft(char byte, unsigned int nbits)
{
	/*doesnt work here for some reason
	worked fine in bitarr :)*/
	return (byte >> (8 - nbits)) | (byte << nbits);
}

void RotateTest(void)
{
	RotateLeft((char)128, 1) == 1 ? printf("Success\n") : printf("Failure");
}
	
void SwapPointers(void **p1, void **p2)
{
	void *temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}	

void SwapPointersTest(void)
{
	int a = 5;
	int b = 6;
	int *p1 = &a;
	int *p2 = &b;
	SwapPointers((void **)&p1, (void **)&p2);
	a == *p2 ? printf("Success\n") : printf("Failure");
	b == *p1 ? printf("Success\n") : printf("Failure");
}

size_t Strlen (const char *str)
{
	size_t counter = 0;
	
	assert(NULL != str);
	
	while ('\0' != *str)
	{
		++counter;
		++str;
	}
	
	return counter;
}

int Strcmp(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
	
	while (*s1 == *s2 && '\0' != *s1)
	{
		++s1;
		++s2;
	}
	
	return *s1 - *s2;
}

char *Strcpy(char *dest, const char *src)
{
	char *d_runner = dest;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	while ('\0' != *src)
	{
		*d_runner = *src;
		++d_runner;
		++src;
	}
	
	*d_runner = *src;
	
	return dest;
}

char *Strncpy(char *dest, const char *src, size_t n)
{
	char *d_runner = dest;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	
	--n;
	
	while ('\0' != *src && 0 < n)
	{
		*d_runner = *src;
		++d_runner;
		++src;
		--n;
	}
	
	*d_runner = *src;
	
	return dest;
}

char *Strcat(char *dest, const char *src)
{
	char *d_runner = dest;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	while ('\0' != *d_runner)
	{
		++d_runner;
	}
	
	
	while ('\0' != *src)
	{
		*d_runner = *src;
		++d_runner;
		++src;
	}
	
	*d_runner = *src;
	
	return dest;
}


void StringTest(void)
{
	char str1[20] = "abcdefg";
	char str2[20] = {0};
	char str3[20] = {0};
	
	Strlen(str1) == 7 ? printf("Success\n") : printf("Failure");
	Strcmp(str1, str2) != 0 ? printf("Success\n") : printf("Failure");
	Strcpy(str2, str1);
	Strcmp(str1, str2) == 0 ? printf("Success\n") : printf("Failure");
	Strncpy(str3, str1, 4);
	Strcmp(str3, "abcd") == 0 ? printf("Success\n") : printf("Failure");
	Strcat(str3, str2);
	Strcmp(str3, "abcdabcdefg") == 0 ? printf("Success\n") : printf("Failure");
}


unsigned long GetNFibonacciElement(unsigned int n)
{
	size_t prev = 0;
	size_t curr =1;
	size_t ans = prev + curr;
	size_t i = 0;
	
	--n;
	
	for (i = 0; i < n; ++i)
	{
		ans = prev + curr;
		prev = curr;
		curr = ans;
	}
	
	return ans;
}

void FibonacciTest(void)
{
	GetNFibonacciElement(1) == 1 ? printf("Success\n") : printf("Failure");
	GetNFibonacciElement(2) == 1 ? printf("Success\n") : printf("Failure");
	GetNFibonacciElement(3) == 2 ? printf("Success\n") : printf("Failure");
	GetNFibonacciElement(6) == 8 ? printf("Success\n") : printf("Failure");
	GetNFibonacciElement(8) == 21 ? printf("Success\n") : printf("Failure");
}

char *IntToString(char *str, int num)
{
	sprintf(str, "%d", num);
	return str;
}

void IntToStrTest(void)
{
	char str[20] = {0};
	IntToString(str, 3);
	str[0] == '3' ? printf("Success\n") : printf("Failure");
	IntToString(str, 23);
	str[0] == '2' ? printf("Success\n") : printf("Failure");
	str[1] == '3' ? printf("Success\n") : printf("Failure");
}

int MulByEight(int num)
{
	/*int is_negative = 0;
	
	if (0 < num)
	{
		is_negative = 1;
		num *= -1;
	}
	*/
	num <<= 3;
	
	/*return is_negative? -num : num;*/
	return num;
}

void MulByEightTest(void)
{
	MulByEight(1) == 8 ? printf("Success\n") : printf("Failure");
	MulByEight(-2) == -16 ? printf("Success\n") : printf("Failure");	
	MulByEight(10) == 80 ? printf("Success\n") : printf("Failure");
}




int main(void)
{
	struct S1 s1 = {NULL, 0, 0, NULL};
	printf("sizeof s1 = %ld\n", sizeof(s1));
	
	printf("Testing FlipDigitsInNum Q1\n");
	FlipDigitsTest(123, 321);
	FlipDigitsTest(5, 5);
	FlipDigitsTest(-234, -432);
	FlipDigitsTest(0, 0);
	printf("\n\n");
	
	printf("Testing MirrorByte Q4\n");
	MirrorByteTest();
	printf("\n\n");
	
	printf("Testing FlipBit Q5\n");
	FlipBitTest();
	printf("\n\n");
	
	printf("Testing CountBits Q6\n");
	CountBitsTest();
	printf("\n\n");
	
	printf("Testing RotateLeft Q8\n");
/*	RotateTest();*/
	printf("\n\n");	
	
	printf("Testing SwapPointers Q10\n");
	SwapPointersTest();
	printf("\n\n");	
	
	printf("Testing String functions Q11\n");	
	StringTest();
	printf("\n\n");	
	
	printf("Testing Fibonacci Q12\n");		
	FibonacciTest();
	printf("\n\n");			
	
	printf("Testing IntToString Q13\n");				
	IntToStrTest();
	printf("\n\n");			
	
	printf("Testing MulByEight Q14\n");
	MulByEightTest();	
	printf("\n\n");
	
	/*foo();*/
/*	foo2();*/
	printf("Sizeof struct s1 = %ld\n", sizeof(struct S1));
	printf("Sizeof struct s2 = %ld\n", sizeof(struct S2));
	return 0;
}