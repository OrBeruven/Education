/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <string.h>

void SwapChar(char *c1, char *c2);
void PrintPermutation(char *string, size_t left, size_t right);

void SwapChar(char *c1, char *c2)
{
    char temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

void PrintPermutation(char *string, size_t left, size_t right)
{
    size_t i = 0;
    
    if (left == right)
    {
        printf("%s\n", string);
    }
    else 
    {
        for (i = left; i <= right; ++i) 
        {
            SwapChar((string + left), (string + i));
            PrintPermutation(string, left + 1, right);
            SwapChar((string + left), (string + i));
        }
    }
}

int main(void)
{
	char str[] = "ABCD";
    int n = strlen(str);
    PrintPermutation(str, 0, n - 1);
	return 0;
}
