#include <stdio.h>	/* printf */

#include "migv1.h"

int x = 5;

void PrintGlobalVariableAddress()
{
	printf("Global Variable address: %p\n", &x);
}
