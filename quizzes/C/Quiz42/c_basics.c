/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdlib.h> /*size_t*/
#include <stdio.h>  /*printf*/
#include <string.h> /*memset*/
#include <assert.h>	/*assert*/

#include "utilitiestwo.h"

#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
/*Q1*/
int SecondAndSixth(unsigned char byte)
{
    return ((byte >> 1) & 1) && ((byte >> 5) & 1);
}

int SecondOrSixth(unsigned char byte)
{
    return ((byte >> 1) & 1) || ((byte >> 5) & 1);
}

void Swap3_5 (unsigned char *byte)
{
    *byte = *byte ^ 20;
}

/*Q2*/
void SwapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*Q3*/
void SwapIntPointers(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}

/*Q4*/
void SwapVoidPointers(void **a, void **b)
{
    size_t *temp = *(size_t **)a;
    *(size_t **)a = *(size_t **)b;
    *(size_t **)b = temp;
}


/*Q6*/
int *CreateArr(size_t size)
{
    return (int *)calloc(size, sizeof(int));
}

/*Q7*/
int **CreateMat(size_t rows, size_t cols)
{
    size_t i = 0;
    int **mat = (int **)malloc(sizeof(int *) * rows);

    for (i = 0; i < rows; ++i)
    {
        mat[i] = (int *)malloc(sizeof(int) * cols);
    }

    return mat;
}

/*Q8*/
void ArrReset(int *arr, size_t size)
{
    memset(arr, 0, size * sizeof(int));
}

/*Q9*/
void MatReset(int **mat, size_t rows, size_t cols)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            mat[i][j] = 0;
        }
    }
}
/*******************************************************************************

*******************************************************************************/

int main(void)
{
    unsigned char swap35 = 0;
    int swap1 = 10;
    int swap2 = 20;
    int *swap_p1 = (int *)1;
    int *swap_p2 = (int *)2;
    void *v_p1 = (void *)1;
    void *v_p2 = (void *)2;
    int *arr = NULL;
    int **mat = NULL;
    size_t i = 0;
    /*Test 2 and 6 ON
        10010110 = 150 = false
        10110100 = 180 = false
        10111010 = 186 = true*/

    HEADER(Testing Q1 Second and Sixth);
    RESULT_STATUS(SecondAndSixth(150), 0, FALSE);
    RESULT_STATUS(SecondAndSixth(180), 0, FALSE);
    RESULT_STATUS(SecondAndSixth(186), 1, TRUE);

    /*Test 2 Or 6
        10010110 = 150 = true
        10110100 = 180 = true
        10111010 = 186 = true
        10000001 = 129 = false*/

    HEADER(Testing Q1 Second and Sixth);
    RESULT_STATUS(SecondOrSixth(150), 1, TRUE);
    RESULT_STATUS(SecondOrSixth(180), 1, TRUE);
    RESULT_STATUS(SecondOrSixth(186), 1, TRUE);
    RESULT_STATUS(SecondOrSixth(129), 0, FALSE);

    /*Swap 3 and 5
        10010110 = 150 = 150
        10100100 = 164 = 176
        10101000 = 168 = 168
        10111000 = 184 = 172*/

    HEADER(Testing Swap 3 and 5);
    swap35 = 168;
    Swap3_5(&swap35);
    printf("%d\n", swap35);
    RESULT_STATUS(swap35, 168, );

    swap35 = 184;
    Swap3_5(&swap35);
    RESULT_STATUS(swap35, 172, );


    HEADER(Q2 Testing Swap ints);
    RESULT_STATUS(1, 1, Before Swap 10 and 20);
    SwapInt(&swap1, &swap2);
    RESULT_STATUS(swap1 == 20, 1, swap1 = 20);
    RESULT_STATUS(swap2 == 10, 1, swap2 = 10);

    HEADER(Q3 Testing Swap pointers);
    RESULT_STATUS(1, 1, Before Swap 1 and 2);
    SwapIntPointers(&swap_p1, &swap_p2);
    RESULT_STATUS((long int)swap_p1 == 2, 1, swap_p1 = 2);
    RESULT_STATUS((long int)swap_p2 == 1, 1, swap_p2 = 1);

    HEADER(Q4 Testing Swap void pointers);
    RESULT_STATUS(1, 1, Before Swap 1 and 2);
    SwapVoidPointers(&v_p1, &v_p2);
    RESULT_STATUS((long int)v_p1 == 2, 1, v_p1 = 2);
    RESULT_STATUS((long int)v_p2 == 1, 1, v_p2 = 1);

    HEADER(Q6 & Q8 Create and reset array);
    arr = CreateArr(5);
    RESULT_STATUS(arr != NULL, 1, Create Array);
    arr[2] = 3;
    ArrReset(arr, 5);
    RESULT_STATUS(arr[2] == 0, 1, Reset Array);
    free(arr);

    HEADER(Q7 & Q8 Create and reset matrix);
    mat = CreateMat(5, 5);
    RESULT_STATUS(mat != NULL, 1, Create Matrix);
    mat[2][2] = 3;
    MatReset(mat, 5, 5);
    RESULT_STATUS(mat[2][2] == 0, 1, Reset Matrix);
    
    for (i = 0; i < 5; ++i)
    {
        free(mat[i]);
    }
    free(mat);
    
    return 0;
}