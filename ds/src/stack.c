/*******************************
Dev: Aaron Sarfaty
Rev: Mor
Date: 26.1.23
********************************/

#include <stdlib.h> /*malloc*/
#include <stdio.h> /*perror*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/

#include "../include/stack.h"


struct stack {
	void *data;
	size_t top;
	size_t capacity;
	size_t i_size;
};


stack_t *StackCreate(size_t capacity, size_t item_size)
{
	stack_t *stack1 = (stack_t*)malloc(sizeof(stack_t));

	if (NULL == stack1)
	{
		perror("Allocation error\n");
		return NULL;
	}

	stack1->data = malloc(capacity * item_size);

	if (NULL == stack1->data)
	{
		perror("Allocation error\n");
		return NULL;
	}
	stack1->top = 0;
	stack1->capacity = capacity;
	stack1->i_size = item_size;
	return stack1;
}

void StackDestroy(stack_t *stack)
{
	assert (NULL != stack);

	stack->top = 0;
	free(stack->data);
	free(stack);	

	return;
}
void StackPush(stack_t *stack, const void *item)
{
	assert (NULL != stack);
	assert (NULL != item);
	assert (StackCapacity(stack) != StackSize(stack));

	memmove((char *)(stack->data) + (stack->top * stack->i_size), item, stack->i_size);
	++stack->top;
	return ;
}


void StackPop(stack_t *stack)
{
	assert (NULL != stack);
	assert (1 != StackIsEmpty(stack));

	--stack->top;
	
	return;
}

void *StackPeek(const stack_t *stack)
{
	void *ret = NULL;
	
	assert (NULL != stack);

	if (!StackIsEmpty(stack))
	{
		ret = ((void *)((char *)stack->data + ((stack->top - 1) * stack->i_size)));
		return ret;
	}
	else
	{
	return NULL;
	}
}
	
int StackIsEmpty(const stack_t *stack)
{
	int res = 0;
	
	assert (NULL != stack);
	
	if (0 == stack->top)
	{
		res = 1;
	}

	return res;
}	
size_t StackSize(const stack_t *stack)
{	
	assert (NULL != stack);
	
	return (stack->top);
}
size_t StackCapacity(const stack_t *stack)
{	
	assert (NULL != stack);

	return (stack->capacity);
}
