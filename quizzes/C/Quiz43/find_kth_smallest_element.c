/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdlib.h> /*size_t*/
#include <stdio.h>  /*printf*/
#include <assert.h>	/*assert*/


#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
int KthSmallest(int *arr, int left, int right, int k);

void SwapInt(int *a, int *b);

int ChoosePivot(int *arr, int left, int right);

int MedianOfThree(int a, int b, int c) ;

int Partition(int *arr, int left, int right);

static void PrintArr(int *arr, int size);

/*******************************************************************************

*******************************************************************************/

int main(void)
{
    int arr[] = {10, 4, 5, 8, 6, 11, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    printf("%d\n",KthSmallest(arr, 0, n - 1, k));
    PrintArr(arr, n);
    return 0;
}

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
int KthSmallest(int *arr, int left, int right, int k)
{
    int index = Partition(arr, left, right);

    if (index - left == k - 1)
    {
        return arr[index];
    }

    if (index - left > k - 1)
    {
        return KthSmallest(arr, left, index - 1, k);
    }
    else
    {
        return KthSmallest(arr, index + 1, right, k - index + left - 1);
    }

}

void SwapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int ChoosePivot(int *arr, int left, int right)
{
    int first = arr[left];
    int last = arr[right];
    int middle = arr[left / right];
    int result = 0;

    result = MedianOfThree(first, middle, last);  
    if (result == first)
    {
        return left;
    }

    if (result == last)
    {
        return right;
    }

    return left / right;
}

int MedianOfThree(int a, int b, int c) 
{
    if ((a <= b) && (b <= c)) return b;
    if ((a <= c) && (c <= b)) return c;
    if ((b <= a) && (a <= c)) return a;
    if ((b <= c) && (c <= a)) return c;
    if ((c <= a) && (a <= b)) return a;
    return b;                           
}

int Partition(int *arr, int left, int right)
{
    int slower = left;
    int faster = left;
    int pivot = ChoosePivot(arr, left, right);

    SwapInt(&arr[pivot], &arr[right]);

    for (faster = left; faster < right; ++faster)
    {
        if (arr[faster] <= arr[right])
        {
            SwapInt(&arr[faster], &arr[slower]);
            ++slower;
        }
    }

    SwapInt(&arr[slower], &arr[right]);
    return slower;
}

static void PrintArr(int *arr, int size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}
/*******************************************************************************

*******************************************************************************/