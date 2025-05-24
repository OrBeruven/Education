/*****************************
	Name : Or Beruven

	Reviewed By : Lilach

	Date Test: 18.03.2023

	Description : c file for recursion implementation

*****************************/
#include <string.h>	/*strncmp*/
#include <assert.h>	/*assert*/

#include "recursion.h"
#include "stack.h"

/**************************************************************************************
						Static Functions Decleration
**************************************************************************************/
static void StackRec(stack_t *stack, int x);

/**************************************************************************************
								Functions
**************************************************************************************/
int FiboIter(int n)
{
	size_t prev = 0;
	size_t curr =1;
	size_t ans = prev + curr;
	int i = 0;
	
	assert(0 < n);
	
	if (2 > n)
	{
		return n - 1;
	}
	
	n -= 2;
	for (i = 0; i < n; ++i)
	{
		ans = prev + curr;
		prev = curr;
		curr = ans;
	}
	
	return ans;
}

int FiboRec(int n)
{	
	assert(0 < n);
	
	if (0 == n)
	{
		return 0;
	}
	else if (3 > n)
	{
		return n - 1;
	}
	
	return FiboRec(n - 1) + FiboRec(n - 2);
}

node_t *SLLFlip(node_t *node)
{	
	node_t *temp = NULL;
	
	assert(NULL != node);
	
	if (NULL == node->next)
	{
		return node;
	}
	
	temp = SLLFlip(node->next);
	
	node->next->next = node;
	node->next = NULL;
	
	return temp;
}

stack_t *StackSort(stack_t *stack)
{
	int x = 0;
	
	assert(NULL != stack);
	
	if (StackIsEmpty(stack))
	{
		return stack;
	}
	
	x = *(int *)StackPeek(stack);
	StackPop(stack);
	stack = StackSort(stack);
	
	StackRec(stack, x);
	
	return stack;
}

size_t StrLenRec(const char *s)
{
	assert(NULL != s);
	
	if ('\0' == *s)
	{
		return 0;
	}
	
	return 1 + StrLenRec(++s);
}

int StrCmpRec(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
	
	if ('\0' == *s1 || *s1 != *s2)
	{
		return *s1 - *s2;
	}
	
	return StrCmpRec(++s1, ++s2);
}

char *StrCpyRec(char *dest, const char *src)
{
	assert(NULL != dest);		
	assert(NULL != src);
	
	if ('\0' == *src)
	{
		return NULL;
	}
	
	*dest = *src;
	StrCpyRec(dest + 1, ++src);
	
	return dest;
}

char *StrCatRec(char *dest, const char *src)
{
	assert(NULL != dest);		
	assert(NULL != src);
	
	if ('\0' == *dest && '\0' != *src)
	{
		*dest = *src;
		*(dest + 1) = '\0';
		StrCatRec(++dest, ++src);
	}
	else if ('\0' != *src)
	{
		StrCatRec(dest + 1, src);
	}
	
	return dest;
}

char *StrStrRec(const char *haystack, const char *needle)
{
	assert(NULL != haystack);		
	assert(NULL != needle);
	
	if ('\0' == *haystack)
	{
		return NULL; 
	}
	
	if (0 == strncmp(haystack, needle, StrLenRec(needle)))
	{
		return (char *)haystack;
	}
	
	return StrStrRec(++haystack, needle);
}

/**************************************************************************************
								Help Functions
**************************************************************************************/
static void StackRec(stack_t *stack, int x)
{
	int temp = 0;
	
	if (StackIsEmpty(stack) || x < *(int *)StackPeek(stack))
	{
		StackPush(stack, &x);
		return;
	}
	
	temp = *(int *)StackPeek(stack);
	StackPop(stack);
	StackRec(stack, x);
	StackPush(stack, &temp);
}
