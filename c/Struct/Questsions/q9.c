/***************
Name: Or Beruven
Tester:
Date Test:
***************/
#include <stdio.h>

struct s
{
  int x : 2;
  char c;
  int y : 4;
};

int main(void)
{	
	struct s s1 = {0, 'c', 1};
	printf("%ld\n", sizeof(s1));
	
	return 0;
}
