/***************
Name: Or Beruven
Tester:
Date Test:
***************/

#include <stdio.h>
#include "g.h"

int g_s = 3;

int main()
{
	printf("The value of g_s = %d\n", g_s);	
	Foo();
	printf("The value of g_s = %d\n", g_s);
	return 0;
}
