/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <string.h>


#include "../../ds/include/stack.h"


void IsBalanced(char *str)
{
	size_t index_first = 0;
	size_t index_curr = 0;
	size_t i = 1;
	/*
	if (str[0] != 123 && str[0] != 91 && str[0] && 40)
	{
		printf("Not Balanced\n");
		return;
	}*/
	
	while ('\0' != str[i])
	{
		while (125 != str[i] && 93 != str[i] && 41 != str[i])
		{
			++i;
			++index_curr;
		}
		
		if (str[i] != str[index_curr] + 1 && str[i] != str[index_curr] + 2)
		{
			printf("Not Balanced\n");
			return;
		}
		
		if (index_curr == index_first)
		{
			index_first = i;
		}
		++i;
		index_curr = index_first;
	}
	
	printf("Balanced\n");

	return;
}

static int IsMatching(char ch1, char ch2)
{
	if (ch1 == '(' && ch2 == ')')
	{
		return 1;
	}
	else if (ch1 == '{' && ch2 == '}')
	{
		return 1;
	}
	else if (ch1 == '[' && ch2 == ']')
	{ 
		return 1;
	}
	else
	{
		return 0;
	}
}

void IsBalancedStack(char *str)
{
	size_t i = 0;
	void *ip = NULL;
	stack_t *stack = StackCreate(strlen(str), 1);
	
	while ('\0' != str[i])
	{
		if ('{' == str[i] || '(' == str[i] || '[' == str[i])
		{
			ip = *(void **)&str[i];
			StackPush(stack, ip);
		}
		
		if ('}' == str[i] || ')' == str[i] || ']' == str[i])
		{
			if (StackIsEmpty(stack))
			{
				printf("Not Balanced\n");
				StackDestroy(stack);
				return;
			}
			else if (!IsMatching(*(char *)StackPeek(stack), str[i]))
			{
				printf("Not Balanced\n");
				StackDestroy(stack);
				return;
			}
			
			StackPop(stack);
		}
		
		++i;
	}
	
	if (StackIsEmpty(stack))
	{
		printf("Balanced\n");
		StackDestroy(stack);
		return;
	}
	else
	{
		printf("Not Balanced\n");
		StackDestroy(stack);
		return;
	}
	
	
	StackDestroy(stack);
	
}
	

int main(void)
{
	char str[20] = "[()](){[()]()}";
	IsBalancedStack(str);
	return 0;
}


