/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*NULL*/
#include <assert.h>	/*assert*/

#include "stack.h"

#define STACK_SIZE 10

#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
void StackSort(stack_t *stack);

void StackSortHelp(stack_t *stack, void *num);

void PrintStack(stack_t *stack);
/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                                Main
*******************************************************************************/
int main(void)
{
    int num1 = 222;
    int num2 = 111;
    int num3 = 235;
    int num4 = 752;
    int num5 = 2;
    int num6 = 53;
    int num7 = 234;
    int num8 = 5;
    int num9 = 6;
    stack_t *stack = StackCreate(STACK_SIZE, sizeof(int));

    StackPush(stack, &num1);
    StackPush(stack, &num4);
    StackPush(stack, &num5);
    StackPush(stack, &num6);
    StackPush(stack, &num3);
    StackPush(stack, &num9);
    StackPush(stack, &num2);
    StackPush(stack, &num8);
    StackPush(stack, &num7);

    PrintStack(stack);
    PrintStack(stack);

    StackSort(stack);
    PrintStack(stack);
    PrintStack(stack);

    StackDestroy(stack);

    return 0;
}

/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
void StackSort(stack_t *stack)
{
    int num = 0;

    if (1 == StackIsEmpty(stack))
    {
        return;
    }

    num = *(int *)StackPeek(stack);
    StackPop(stack);

    StackSort(stack);
 
    StackSortHelp(stack, &num);
    return;
}

void StackSortHelp(stack_t *stack, void *num)
{
    int temp = 0;

    if (1 == StackIsEmpty(stack) || *(int *)num > *(int *)StackPeek(stack))
    {
        StackPush(stack, num);
        return;
    }

    temp = *(int *)StackPeek(stack);
    StackPop(stack);

    StackSortHelp(stack, num);

    StackPush(stack, &temp);
}

void PrintStack(stack_t *stack)
{
    stack_t *stack2 = StackCreate(STACK_SIZE, sizeof(int));

    while (1 != StackIsEmpty(stack))
    {
        printf("%d, ", *(int *)StackPeek(stack));
        StackPush(stack2, StackPeek(stack));
        StackPop(stack);
    }
    printf("\n");
    while (1 != StackIsEmpty(stack2))
    {
        StackPush(stack, StackPeek(stack2));
        StackPop(stack2);
    }

    StackDestroy(stack2);
}

/*******************************************************************************

*******************************************************************************/