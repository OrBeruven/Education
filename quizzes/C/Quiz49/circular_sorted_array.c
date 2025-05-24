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
int FindAnElementInACircularSortedArray(int *arr, size_t size, int element);

static int FindStartIndex(int *arr, int left, int right);

static int BinarySearch(int *arr, int left, int right, int element);

static void PrintArr(int *arr, int size);

/*******************************************************************************

*******************************************************************************/

int main(void)
{
    int arr[] = {10, 11, 4, 5, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", FindAnElementInACircularSortedArray(arr, n - 1, 8));
    PrintArr(arr, n);
    return 0;
}

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
int FindAnElementInACircularSortedArray(int *arr, size_t size, int element)
{
    int pivot = FindStartIndex(arr, 0, size - 1);

    if (arr[pivot] == element)
    {
        return pivot;
    }
    else if (arr[0] <= element)
    {
        return BinarySearch(arr, 0, pivot - 1, element);
    }
    else
    {
        return BinarySearch(arr, pivot + 1, size - 1, element);
    }

}

static int FindStartIndex(int *arr, int left, int right)
{
    int mid = 0;

    if (right < left)
    {
        return -1;
    }
    if (right == left)
    {
        return left;
    }

    mid = (left + right) / 2;

    if (mid < right && arr[mid] > arr[mid + 1])
    {
        return mid;
    }
    if (mid > left && arr[mid] < arr[mid - 1])
    {
        return (mid - 1);
    }
    if (arr[left] >= arr[mid])
    {
        return FindStartIndex(arr, left, mid - 1);
    }
    return FindStartIndex(arr, mid + 1, right);
}

static int BinarySearch(int *arr, int left, int right, int element)
{
    int mid = (left + right) / 2;

    if (element == arr[mid])
    {
        return mid;
    }
    if (element > arr[mid])
    {
        return BinarySearch(arr, mid + 1, right, element);
    }
    else
    {
        return BinarySearch(arr, left, mid - 1, element);
    }
}
static void PrintArr(int *arr, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}
/*******************************************************************************

*******************************************************************************/