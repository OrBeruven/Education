#include <stdio.h>
#include <string.h>

int StrRotation(char *s1, char *s2)
{
	size_t s2_index = 0;
	size_t counter = 0;
	size_t s1_size = strlen(s1);

	if (strlen(s2) == s1_size)
	{
		for (counter = 0; counter < s1_size; ++counter)
		{
			if(s1[0] == s2[counter])
			{
				s2_index = counter;
				break;
			}
		}
		
		for (counter = 0; counter < s1_size; ++counter)
		{
			if(s2_index >= s1_size)
			{
				s2_index = 0;
			}
			
			if(s1[counter] != s2[s2_index])
			{
				break;
			}
			
			++s2_index;
		}
	}
	return counter == (s1_size) ? 0 : 1;
}
int main(void)
{
	char s1[10] = "abcdef123";
	char s2[10] = "123abcde1";
	
	if(!StrRotation(s1, s2))
	{
		printf("Strings are rotation!");
	}
	else
	{
		printf("Strings are NOT rotation");
	}
	return 0;
}
