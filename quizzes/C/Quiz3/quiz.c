#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*no include to string.h*/
#include <string.h>

int main()
{
	char *str1 = "hello";
	
	/*one more space for '\0'*/
	/*cant get strlen??*/
	char str2[5+1];
	
	char *str3 = (char *)malloc(strlen(str1) + 1);
	
	char *temp = str1;
	char *temp2 = str3;
	
	while (*str1)
	{
		*str3 = *str1;
		++str3;
		++str1;
	}
	
	/*str1 points to end of string*/
	str1 = temp;
	str3 = temp2;
	
	strcpy(str2, str1);
	
	
	
	/*trying to set value to pointer
	who didnt dynamic allocate space.
	you cant set value to pointer	*/
	if (islower(*str1))
	{
		/**str1 = toupper(*str1);*/
	}
	
	/*str3 was invalid pointer. now set back to head*/
	free(str3);
	str3 = NULL;


	printf("The str1 = %s\n", str1);
	printf("The str2 = %s\n", str2);
	printf("The str3 = %s\n", str3);
	
	/*no return 0*/
	return 0;	
}
