/*****************************
	Name : Or Beruven

	Reviewed By : Lihi Cohen

	Date Test: 30.1.2023

	Description : header file for Stack

*****************************/

#ifndef STACK_H
#define STACK_H

typedef struct stack stack_t;

stack_t *StackCreate(size_t capacity, size_t item_size);

void StackDestroy(stack_t *stack);

void StackPush(stack_t *stack, const void *item);

void StackPop(stack_t *stack);

void *StackPeek(const stack_t *stack);

int StackIsEmpty(const stack_t *stack);

size_t StackSize(const stack_t *stack);

size_t StackCapacity(const stack_t *stack);

#endif
