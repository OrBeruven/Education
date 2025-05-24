/*****************************
	Name : Or Beruven

	Reviewed By : Lihi Cohen

	Date Test: 30.1.2023

	Description : c file for stack_test

*****************************/

#include <stdio.h>

#include "../include/stack.h"

int main(void)
{
    stack_t *mystack = StackCreate(4, 4);
    float a = 1.2;
    float b = 2.3;
    float c = 3.5;
    float d = 4.6;
    float e = 5.7;
    
    printf("before push, capacity is %lu\n", StackCapacity(mystack));
    printf("before push, size is %lu\n", StackSize(mystack));
    printf("before push, StackIsEmpty returns is %d\n", StackIsEmpty(mystack));
    StackPush(mystack, &a);
    printf("after push, capacity is %lu\n", StackCapacity(mystack));
    printf("after push, size is %lu\n", StackSize(mystack));
    printf("after push, StackIsEmpty returns is %d\n", StackIsEmpty(mystack));
    
    
    StackPush(mystack, &b);
    printf("after push1, capacity is %lu\n", StackCapacity(mystack));
    printf("after push, size is %lu\n", StackSize(mystack));
    StackPush(mystack, &c);
    printf("after push2, capacity is %lu\n", StackCapacity(mystack));
    printf("after push, size is %lu\n", StackSize(mystack));
    StackPush(mystack, &d);
    printf("after push3, capacity is %lu\n", StackCapacity(mystack));
    printf("after push, size is %lu\n", StackSize(mystack));
    
    printf("testing pop\n");
    StackPop(mystack);
    StackPop(mystack);
    printf("After 2 pops, peek returns %f\n", *(float *)(StackPeek(mystack)));
    printf("Deleting stack\n");
    StackDestroy(mystack);
    
    return 0;
}

