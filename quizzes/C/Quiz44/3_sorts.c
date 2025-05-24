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
void QuickSort(int *arr, int left, int right);
/*Quick Sort Help Function*/
int ChoosePivot(int *arr, int left, int right);
int MedianOfThree(int a, int b, int c) ;
int Partition(int *arr, int left, int right);
/*************************/

void MergeSort(int *arr, int left, int right);
/*Merge Sort Help Function*/
void Merge(int *arr, int left, int mid, int right);
/*************************/

void SelectionSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void BubbleSort(int *arr, size_t size);

void HeapSort(int *arr, int size);
/*Heap Sort Help Function*/
static void Heapify(int *arr, int size, int i);
/*************************/

void SwapInt(int *a, int *b);

static void PrintArr(int *arr, size_t size);

/*******************************************************************************

*******************************************************************************/

int main(void)
{
    int qsort_arr[] = {10, 4, 5, 8, 6, 11, 26};
    int qsort_n = sizeof(qsort_arr) / sizeof(qsort_arr[0]);

    int merge_arr[] = {10, 4, 5, 8, 6, 11, 26};
    int merge_n = sizeof(merge_arr) / sizeof(merge_arr[0]);

    int select_arr[] = {10, 4, 5, 8, 6, 11, 26};
    int select_n = sizeof(select_arr) / sizeof(select_arr[0]);

    int insert_arr[] = {10, 4, 5, 8, 6, 11, 26};
    int insert_n = sizeof(insert_arr) / sizeof(insert_arr[0]);

    int bubble_arr[] = {10, 4, 5, 8, 6, 11, 26};
    int bubble_n = sizeof(bubble_arr) / sizeof(bubble_arr[0]);

    int heap_arr[] = {10, 4, 5, 8, 6, 11, 26};
    int heap_n = sizeof(heap_arr) / sizeof(heap_arr[0]);

    QuickSort(qsort_arr, 0, qsort_n - 1);
    PrintArr(qsort_arr, qsort_n);

    MergeSort(merge_arr, 0, merge_n - 1);
    PrintArr(merge_arr, merge_n);

    SelectionSort(select_arr, select_n);
    PrintArr(select_arr, select_n);

    InsertionSort(insert_arr, insert_n);
    PrintArr(insert_arr, insert_n);

    BubbleSort(bubble_arr, bubble_n);
    PrintArr(bubble_arr, bubble_n);

    HeapSort(heap_arr, heap_n);
    PrintArr(heap_arr, heap_n);

    return 0;
}

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
void QuickSort(int *arr, int left, int right)
{
    int index = 0;
    
    if (left < right)
    {
        index = Partition(arr, left, right);

        QuickSort(arr, left, index - 1);
        QuickSort(arr, index + 1, right);
    }
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

void MergeSort(int *arr, int left, int right)
{
    int mid = 0;

    if (left < right)
    {
        mid = (left + right) / 2;

        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

void Merge(int *arr, int left, int mid, int right)
{
    size_t i = 0;
    size_t j = 0;
    size_t arr_index = 0;
    size_t left_len = mid - left + 1;
    size_t right_len = right - mid;

    int *left_arr = NULL;
    int *right_arr = NULL;

    left_arr = (int *)malloc(sizeof(int) * left_len);
    if (NULL == left_arr)
    {
        perror("Malloc in merge");
        return;
    }
    right_arr = (int *)malloc(sizeof(int) * right_len);
    if (NULL == right_arr)
    {
        free(left_arr);
        perror("Malloc in merge");
        return;
    }

    for (i = 0; i < left_len; ++i)
    {
        left_arr[i] = arr[left + i];
    }

    for (i = 0; i < right_len; ++i)
    {
        right_arr[i] = arr[mid + i + 1];
    }

    i = 0;
    j = 0;
    arr_index = left;

    while (j < right_len && i < left_len)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[arr_index] = left_arr[i];
            ++i;
        }
        else
        {
            arr[arr_index] = right_arr[j];
            ++j;
        }

        ++arr_index;
    }

    while (i < left_len)
    {
        arr[arr_index] = left_arr[i];
        ++i;
        ++arr_index;
    }

    while (j < right_len)
    {
        arr[arr_index] = right_arr[j];
        ++j;
        ++arr_index;
    }

    free(left_arr);
    free(right_arr);
}

void SelectionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    int min_index = 0;

    for (i = 0; i < size; ++i)
    {
        min_index = i;
        for (j = i; j < size; ++j)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        SwapInt(&arr[i], &arr[min_index]);
    }
}

void InsertionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < size; ++i)
    {
        j = i;
        while (j > 0 && arr[j] < arr[j - 1])
        {
            SwapInt(&arr[j], &arr[j - 1]);
            --j;
        }
    }
}

void BubbleSort(int *arr, size_t size)
{
    int has_changed = 1;
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < size - 1 && has_changed == 1; ++i)
    {
        has_changed = 0;

        for (j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                has_changed = 1;
                SwapInt(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void HeapSort(int *arr, int size)
{
    int i = 0;

    for (i = size / 2 - 1; i >= 0; --i)
    {
        Heapify(arr, size, i);
    }

    for (i = size - 1; i >= 0; --i)
    {
        SwapInt(&arr[0], &arr[i]);
        Heapify(arr, i, 0);
    }
}

static void Heapify(int *arr, int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        SwapInt(&arr[i], &arr[largest]);
        Heapify(arr, size, i);
    }
}

void SwapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void PrintArr(int *arr, size_t size)
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