#include <stdio.h>
#include <stdlib.h>

void CoreDumpInfinity();

int main(void)
{

/*q2
	char strq3[10] = "This is 3";
	

		
	char *str = (char *)malloc(sizeof(char) * 10);
	
	str = "This is 1";
	
	printf("%s\n", str);
*/
/*q3

	
	printf("letter in 11th place - %c\n", strq3[11]);
	
*/



/*q4
	
	char strq4[10] = "This is 4";
	strq4[11] = 'c';
	
	printf("letter in 11th place - %c\n", strq4[11]);
*/

/*q5
	char *strq5 = (char *)malloc(sizeof(char) * 10);
	free(strq5);
	
	printf("%c\n", *strq5);
*/

/*q6
	char *strq6 = (char *)malloc(sizeof(char) * 10);
	
	if(*strq6)
	{
		printf("Entered if\n");
	}
	else
	{
		printf("Didnt entered\n");
	}
	
	free(strq6);
*/


/*q2 - Core Dump*/
	CoreDumpInfinity();

	
	
	return 0;
	
}


void CoreDumpInfinity()
{
	while(1)
	{
		printf("AHAHAAHAHHAHAAHHA");
	}
}
















