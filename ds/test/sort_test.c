/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include <stdlib.h> /*rand, qsort*/
#include <time.h>	/*clock_t*/

#include "sort.h"
#include "utilitiestwo.h"

#define ARR_SIZE 5000
#define SMALL_ARR_SIZE 6

#define NUM_RANGE 100
#define SEVEN_DIGIT_MAX 9999999
#define SEVEN_DIGIT_MIN 1000000

#define SORTED 1
#define NOT_SORTED 0

#define SAME 1
#define NOT_SAME 0

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void BubbleSortTest(void);

static void SelectionSortTest(void);

static void InsertionSortTest(void);

static void CountingSortTest(void);

static void RadixSortTest(void);

static void BinarySearchTest(void);

static void MergeSortTest(void);

static void QuickSortTest(void);
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						help function declarations
*******************************************************************************/
int cmp_func(const int data1, const int data2);

int qsort_cmp_func (const void * a, const void * b);

static void PrintArr(int arr[], size_t size);

static int IsSorted(int arr[], size_t size);

static int IsSameArr(int arr1[], int arr2[], size_t size);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	/*HEADER(Testing Bubble Sort);
	BubbleSortTest();
	printf("\n");
	
	HEADER(Testing Selection Sort);
	SelectionSortTest();
	printf("\n");
	
	HEADER(Testing Insertion Sort);
	InsertionSortTest();
	printf("\n");
	
	HEADER(Testing Counting Sort);
	CountingSortTest();
	printf("\n");
	
	HEADER(Testing Radix Sort);
	RadixSortTest();
	printf("\n");*/
	
	HEADER(Testing Binary Search);
	BinarySearchTest();
	printf("\n");
	
	HEADER(Testing Merge Search);
	MergeSortTest();
	printf("\n");
	
	HEADER(Testing Quick Search);
	QuickSortTest();
	printf("\n");
	return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/
static void BubbleSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	int qarr[ARR_SIZE] = {0};
	size_t i = 0;
	
	clock_t time = 0;
	double sort_time = 0;
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % NUM_RANGE;
		qarr[i] = arr[i];
	}
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), NOT_SORTED, BeforeSort);
	
	time = clock();
	BubbleSort(arr, ARR_SIZE, cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), SORTED, AfterSort);

	printf("Your function took %f seconds to execute\n", sort_time);

	time = clock();
	qsort(qarr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	printf("qsort function took %f seconds to execute\n", sort_time);
	
	RESULT_STATUS(IsSameArr(arr, qarr, ARR_SIZE), SAME, Same Result As qsort);

}

static void SelectionSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	int qarr[ARR_SIZE] = {0};
	size_t i = 0;
	
	clock_t time = 0;
	double sort_time = 0;
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % NUM_RANGE;
		qarr[i] = arr[i];
	}
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), NOT_SORTED, BeforeSort);
	
	time = clock();
	SelectionSort(arr, ARR_SIZE, cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), SORTED, AfterSort);

	printf("Your function took %f seconds to execute\n", sort_time);

	time = clock();
	qsort(qarr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	printf("qsort function took %f seconds to execute\n", sort_time);
	
	RESULT_STATUS(IsSameArr(arr, qarr, ARR_SIZE), SAME, Same Result As qsort);
	
}

static void InsertionSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	int qarr[ARR_SIZE] = {0};
	size_t i = 0;
	
	clock_t time = 0;
	double sort_time = 0;
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % NUM_RANGE;
		qarr[i] = arr[i];
	}
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), NOT_SORTED, BeforeSort);
	
	time = clock();
	InsertionSort(arr, ARR_SIZE, cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), SORTED, AfterSort);

	printf("Your function took %f seconds to execute\n", sort_time);

	time = clock();
	qsort(qarr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	printf("qsort function took %f seconds to execute\n", sort_time);
	
	RESULT_STATUS(IsSameArr(arr, qarr, ARR_SIZE), SAME, Same Result As qsort);
}

static void CountingSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	int qarr[ARR_SIZE] = {0};
	size_t i = 0;
	int flag = 0;
	
	clock_t time = 0;
	double sort_time = 0;
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % NUM_RANGE;
		if (0 == flag)
		{
			arr[i] *= -1;
			flag = 1;
		}
		else
		{
			flag = 0;
		}
		qarr[i] = arr[i];
	}
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), NOT_SORTED, BeforeSort);
	time = clock();
	flag = CountingSort(arr, ARR_SIZE);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	RESULT_STATUS(flag, 0, Returned Success);
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), SORTED, AfterSort);
	printf("Your function took %f seconds to execute\n", sort_time);

	time = clock();
	qsort(qarr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	printf("qsort function took %f seconds to execute\n", sort_time);
	RESULT_STATUS(IsSameArr(arr, qarr, ARR_SIZE), SAME, Same Result As qsort);
}

static void RadixSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	int qarr[ARR_SIZE] = {0};
	size_t i = 0;
	int flag = 0;
	
	clock_t time = 0;
	double sort_time = 0;
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % (SEVEN_DIGIT_MAX + 1 - SEVEN_DIGIT_MIN) + SEVEN_DIGIT_MAX;
		qarr[i] = arr[i];
	}
	
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), NOT_SORTED, BeforeSort);

	time = clock();
	flag = RadixSort(arr, ARR_SIZE);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	
	RESULT_STATUS(flag, 0, Returned Success);
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), SORTED, AfterSort);
	printf("Your function took %f seconds to execute\n", sort_time);	
	
	time = clock();
	qsort(qarr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	
	printf("qsort function took %f seconds to execute\n", sort_time);
	RESULT_STATUS(IsSameArr(arr, qarr, ARR_SIZE), SAME, Same Result As qsort);
}

static void BinarySearchTest(void)
{
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	RESULT_STATUS(BinarySearchIterative(arr, 10, 3), 2, Binary);
	RESULT_STATUS(BinarySearchIterative(arr, 10, 0), -1, Error 404);
	RESULT_STATUS(BinarySearchIterative(arr, 10, 5), 4, );
	RESULT_STATUS(BinarySearchIterative(arr, 10, 9), 8, );
	RESULT_STATUS(BinarySearchIterative(arr, 10, 10), 9, );
	
	RESULT_STATUS(BinarySearchRecursive(arr, 10, 3), 2, BinaryRec);
	RESULT_STATUS(BinarySearchRecursive(arr, 10, 5), 4, );
	RESULT_STATUS(BinarySearchRecursive(arr, 10, 9), 8, );
	RESULT_STATUS(BinarySearchRecursive(arr, 10, 10), 9, );
	printf("%lu\n", BinarySearchRecursive(arr, 10, 10));
	RESULT_STATUS(BinarySearchRecursive(arr, 10, 0), -1, Error 404);
}

static void MergeSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	int qarr[ARR_SIZE] = {0};
	size_t i = 0;
	int flag = 0;
	
	clock_t time = 0;
	double sort_time = 0;
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % NUM_RANGE;
		qarr[i] = arr[i];
	}
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), NOT_SORTED, BeforeSort);
	time = clock();
	flag = MergeSort(arr, ARR_SIZE);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	
	RESULT_STATUS(flag, 0, Returned Success);
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), SORTED, AfterSort);
	printf("Your function took %f seconds to execute\n", sort_time);
	
	time = clock();
	qsort(qarr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	
	printf("qsort function took %f seconds to execute\n", sort_time);
	RESULT_STATUS(IsSameArr(arr, qarr, ARR_SIZE), SAME, Same Result As qsort);
}

static void QuickSortTest(void)
{
	int arr[ARR_SIZE] = {0};
	int qarr[ARR_SIZE] = {0};
	size_t i = 0;
	
	clock_t time = 0;
	double sort_time = 0;
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand() % NUM_RANGE;
		qarr[i] = arr[i];
	}
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), NOT_SORTED, BeforeSort);
	time = clock();
	Qsort(arr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	
	RESULT_STATUS(IsSorted(arr, ARR_SIZE), SORTED, AfterSort);
	printf("Your function took %f seconds to execute\n", sort_time);
	
	time = clock();
	qsort(qarr, ARR_SIZE, sizeof(int), qsort_cmp_func);
	time = clock() - time;
	sort_time = ((double)time)/CLOCKS_PER_SEC;
	printf("qsort function took %f seconds to execute\n", sort_time);
	RESULT_STATUS(IsSameArr(arr, qarr, ARR_SIZE), SAME, Same Result As qsort);
}

/**************************************************************************************
							Helper Functions
**************************************************************************************/
int cmp_func(const int data1, const int data2)
{
	return data1 - data2;
}

int qsort_cmp_func (const void * a, const void * b) 
{
   return ( *(int *)a - *(int *)b );
}

static void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	printf("\n\n");
}

static int IsSorted(int arr[], size_t size)
{
	size_t i = 0;
	int is_sorted = SORTED;
	
	--size;
	for (i = 0; i < size; ++i)
	{
		if (0 < cmp_func(arr[i], arr[i + 1]))
		{
			is_sorted = NOT_SORTED;
			break;
		}
	}
	
	return is_sorted;
}

static int IsSameArr(int arr1[], int arr2[], size_t size)
{
	int is_same = SAME;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			is_same = NOT_SAME;
			break;
		}
	}
	
	return is_same;
}
