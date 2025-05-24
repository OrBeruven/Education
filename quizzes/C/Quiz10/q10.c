/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#define MAX3(a, b, c) ( (a) > (b) ? ( (a) > (c) ? (a) : (c) ) : ( (b) > (c) ? (b) : (c) ) )
#define TO_LOWER(a) ( (64 < (a) && 91 > (a) ) ? (a) + 32 : (a) )
#define OFFSET(s, f) ((long int)&(s).f - (long int)&(s))

#include <stdio.h>


int main(void)
{
	struct s
	{
		int num;
		char ch;
		int num2;
	};
	
	struct s s1 = {6, 'a', 12};
	
	printf("The max is : %d\n", MAX3(5, 12, 4));
	printf("The char A to lower %c\n", TO_LOWER('A'));
	printf("The struct offset is %ld\n", OFFSET(s1, num));
	
	return 0;
}
