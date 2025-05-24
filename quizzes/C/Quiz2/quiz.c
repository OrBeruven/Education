#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void TF(int num);

char *Rev(char *str);

int main(void)
{
	char *str = "abc";
	
	str[0] = 'a';
	/*char *end = str;
	char *temp = (char *)malloc(strlen(str) * sizeof(char) + 1);
	
	if (NULL != str)
	{
		while ('\0' != *end)
		{
			*temp = *end;
			++end;
			++temp;
		}
		*temp = '\0';
		--temp;
		
		end = str;
		while('\0' != *end)
		{
			printf("temp = %c, str = %c\n", *temp, *end);
			*end = 'a';
			++end;
			--temp;
		}
	}
	*/
	printf("%s\n", str);
	return 0;
}

void TF(int num)
{
	int i = 0;
	
	for (i = 1; i <= num; ++i)
	{
		if (0 == i % 3)
		{
			if (0 == i % 5)
			{
				printf("Tf\n");
			}
			else
			{
				printf("T\n");
			}
		}
		else if (0 == i % 5)
		{
			printf("T\n");
		}
		else
		{
			printf("%d\n", i);
		}
	}
}

char *Rev(char *str)
{
	char *end = str;
	char *temp = (char *)malloc(strlen(str) * sizeof(char) + 1);
	
	*str = 'a';
	if (NULL != str)
	{
		while ('\0' != *end)
		{
			*temp = *end;
			++end;
			++temp;
		}
		*temp = '\0';
		--temp;
		
		end = str;
		while('\0' != *str)
		{
			printf("temp = %c, str = %c\n", *temp, *end);
			*end = (char)tolower(*temp);
			++end;
			--temp;
		}
	}
	return NULL;
}		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
