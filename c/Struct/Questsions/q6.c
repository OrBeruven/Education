/***************
Name: Or Beruven
Tester:
Date Test:
***************/

#include <stdio.h>


struct point
{
	int x;
	int y;
};

int main(void)
{
	struct point p = {1, 2};
	int n = *(int *)&p;
	
	printf("%d\n", n);
	
	return 0;
}
