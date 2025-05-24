#include <stdio.h> /*using - printf */

/* local lib functions LutInputKey*/
#include "InputKey.h"

int main(void)
{
	printf("Testing if InputKey\n");
	IfInputKey();
	
	printf("Testing swithc InputKey\n");
	SwitchInputKey();
	
	printf("Testing LUT InputKey\n");
	LutInputKey();
	return 0;
}
