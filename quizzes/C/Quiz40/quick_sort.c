#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 6

void PrintArr(int *arr, ssize_t size);
void Swap(int *a, int *b);
void QuickSort(int *arr, ssize_t size);
void QSort(int *arr, ssize_t start, ssize_t end, size_t pivot_index);

void QSortAnswer(int *arr, ssize_t start, ssize_t end);
static size_t Partition(int *arr, size_t start, size_t end);

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void QuickSort(int *arr, ssize_t size)
{
    QSortAnswer(arr, 0, size - 1);
}

void QSort(int *arr, ssize_t start, ssize_t end, size_t pivot_index)
{
    ssize_t curr = start;
    ssize_t i = 0;

    for (i = start; i < end; ++i)
    {
        if (arr[i] < arr[pivot_index])
        {
            Swap(&arr[i], &arr[curr]);
            ++curr;
        }
    }

    Swap(&arr[curr], &arr[pivot_index]);
    if (start < end)
    {
        QSort(arr, start, curr - 1, pivot_index);
        QSort(arr, curr, end - 1, pivot_index);
    }
}

void QSortAnswer(int *arr, ssize_t start, ssize_t end)
{
    size_t pivot_index = 0;

    if (start < end)
    {
        pivot_index = Partition(arr, start, end);
        QSortAnswer(arr, start, pivot_index - 1);
        QSortAnswer(arr, pivot_index + 1, end);
    }
}

static size_t Partition(int *arr, size_t start, size_t end)
{
    size_t i = start;
    size_t j = 0;

    for (j = start; j < end; ++j)
    {
        if (arr[j] < arr[end])
        {
            Swap(&arr[i], &arr[j]);
            ++i;
        }
    }

    Swap(&arr[i], &arr[end]);

    return i;
}


int main (void)
{
    int arr[SIZE] = {9, -3, 5, 3, 4, 6};
    int arr2[SIZE] = {9, 10, 8, 7, 6, 5};
    QuickSort(arr, SIZE);
    PrintArr(arr, SIZE);

    QuickSort(arr2, SIZE);
    PrintArr(arr2, SIZE);

    return 0;
}

void PrintArr(int *arr, ssize_t size)
{
    ssize_t i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}