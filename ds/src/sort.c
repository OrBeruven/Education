/*****************************
	Name : Or Beruven

	Reviewed By : Moshe the stud

	Date Test:	28.03.2023

	Description : c file for sorting implementation

*****************************/

#include <stdio.h>	/*perror*/
#include <errno.h>	/*errno, ENOMEM*/
#include <stdlib.h>	/*malloc, free, NULL*/
#include <assert.h>	/*assert*/

#include "sort.h"

#define SUCCESS 0
#define FAILURE 1
#define BASE 10

/*******************************************************************************
						help function declarations
*******************************************************************************/
static int RadixCountingSort(int array[], size_t size, size_t mask);
static void SwapInt(int *a, int *b);

/******************************Binary Search***************************************/
static ssize_t BinaryRecursiveSearch(int arr[], size_t low, size_t high, int num);

/********************************Merge Sort***************************************/
static int MergeSortRec(int *arr, size_t left, size_t right);
static int MergeTwoArr(int *arr, size_t left, size_t mid, size_t right);

/********************************Quick Sort***************************************/
static void QuickSortRec(void *base, size_t left, size_t right, size_t size, int (*compar)(const void *, const void *));
static size_t Partition(void *base, size_t left, size_t right, size_t size, int (*compar)(const void *, const void *));
static void SwapData(char *a, char *b, size_t size);
/*******************************************************************************
*******************************************************************************/


/**************************************************************************************
								Functions Implementation
**************************************************************************************/
void BubbleSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t iteration = 0;
	size_t step = 0;
	int flag = 1;
	
	assert(NULL != cmp_func);
	assert(NULL != array);
	
	--size;
	for (step = 0; step < size && 0 != flag; ++step)
	{
		flag = 0;
		for (iteration = 0; iteration < size - step; ++iteration)
		{
			if (0 < cmp_func(array[iteration], array[iteration + 1]))
			{
				SwapInt(&array[iteration], &array[iteration + 1]);
				flag = 1;
			}
		}
	}
}

void SelectionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t step = 0;
	size_t iteration = 0;
	size_t most_cmp_index = 0;
	
	assert(NULL != cmp_func);
	assert(NULL != array);
	
	for (step = 0; step < size - 1; ++step)
	{
		most_cmp_index = step;
		for (iteration = step + 1; iteration < size; ++iteration)
		{
			if (0 > cmp_func(array[iteration], array[most_cmp_index]))
			{
				most_cmp_index = iteration;
			}
		}
		
		SwapInt(&array[step], &array[most_cmp_index]);
	}
}

void InsertionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t step = 0;
	size_t iteration = 0;
	
	assert(NULL != cmp_func);
	assert(NULL != array);
	
	for (step = 1; step < size; ++step)
	{
		iteration = step;
		while (0 < iteration && 0 > cmp_func(array[iteration], array[iteration - 1]))
		{
			SwapInt(&array[iteration], &array[iteration - 1]);
			--iteration;
		}
	}
}

int CountingSort(int array[], size_t size)
{
	int max = 0;
	int min = 0;
	size_t i = 0;
	size_t range = 0;
	
	int *lut = NULL;

	assert(NULL != array);
	
	max = array[0];
	min = array[0];
	for (i = 1; i < size; ++i)
	{
		if (max < array[i])
		{
			max = array[i];
		}
		
		if (min > array[i])
		{
			min = array[i];
		}
	}
	
	if ((max - min) < 0)
	{
		range = (max - min) * -1;
	}
	else
	{
		range = max - min;
	}
	
	lut = (int *)calloc(range + 1, sizeof(int));
	if (NULL == lut)
	{
		errno = ENOMEM;
		perror("CountingSort Malloc");
		return FAILURE;
	}
		 
	for (i = 0; i < size; ++i)
	{
		++lut[array[i] - min];
	}
	
	for (i = 0, max = 0; i <= range; ++i)
	{
		while (lut[i] > 0)
		{
			array[max] = (int)i + min;
			--lut[i];
			++max;
		}
	}
	
	free(lut);
	
	return SUCCESS;
}

int RadixSort(int array[], size_t size)
{
	size_t i = 0;
	
	int max = 0;
	int mask = 1;
	
	assert(NULL != array);
	
	max = array[0];
	for (i = 1; i < size; ++i)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	
	for (mask = 1; 0 != max; max /= 10, mask *= 10)
	{
		if (FAILURE == RadixCountingSort(array, size, mask))
		{
			return FAILURE;
		}
	}
	
	return SUCCESS;
}

ssize_t BinarySearchIterative(int *arr, size_t size, int num)
{
	ssize_t low = 0;
	ssize_t mid = 0;
	ssize_t high = size - 1;
	
	while (low <= high)
	{
		mid = (high + low) / 2; 
		if (arr[mid] == num)
		{
			return mid;
		}
		else if (arr[mid] > num)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	
	return -1;
}

ssize_t BinarySearchRecursive(int *arr, size_t size, int num)
{	
	return BinaryRecursiveSearch(arr, 0, size - 1, num);
}

static ssize_t BinaryRecursiveSearch(int arr[], size_t low, size_t high, int num)
{
	ssize_t mid = (high +  low) / 2;
	
	if (arr[mid] == num)
	{
		return mid;
	}
	
	if (low >= high)
	{
		return -1;
	}
	
	if (arr[mid] < num)
	{
		return BinaryRecursiveSearch(arr, mid + 1, high, num);
	}
	else
	{
		return BinaryRecursiveSearch(arr, low, mid - 1, num);
	}
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	return MergeSortRec(arr_to_sort, 0, num_elements - 1);
}

static int MergeSortRec(int *arr, size_t left, size_t right)
{
	int mid = left + ((right - left) / 2);
	
	if (left >= right)
	{
		return SUCCESS;
	}
	
	if (FAILURE == MergeSortRec(arr, left, mid))
	{
		return FAILURE;
	}
	
	if (FAILURE == MergeSortRec(arr, mid + 1, right))
	{
		return FAILURE;
	}
	
	if (FAILURE == MergeTwoArr(arr, left, mid, right))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}


static int MergeTwoArr(int *arr, size_t left, size_t mid, size_t right)
{
	size_t left_length = mid - left + 1;
	size_t right_length = right - mid;
	
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	int *left_arr = NULL;
	int *right_arr = NULL;
	
	left_arr = (int *)malloc(sizeof(int) * left_length);
	if (NULL == left_arr)
	{
		errno = ENOMEM;
		perror("MergeSort Malloc");
		return FAILURE;
	}
	
	right_arr = (int *)malloc(sizeof(int) * right_length);
	if (NULL == right_arr)
	{
		errno = ENOMEM;
		perror("MergeSort Malloc");
		return FAILURE;
	}
	
	for (i = 0; i < left_length; ++i)
	{
		left_arr[i] = arr[left + i];
	}
	
	for (i = 0; i < right_length; ++i)
	{
		right_arr[i] = arr[mid + 1 + i];
	}
	
	for (i = 0, j = 0, k = left; k <= right; ++k)
	{
		if (i < left_length)
		{
			if (j >= right_length || left_arr[i] <= right_arr[j])
			{
				arr[k] = left_arr[i];
				++i;
			}
			else
			{
				arr[k] = right_arr[j];
				++j;
			}
		}
		else
		{
			arr[k] = right_arr[j];
			++j;
		}
	}
	
	free(left_arr);
	free(right_arr);
	
	return SUCCESS;
}

void Qsort(void *base, size_t num_elements, size_t size, int (*compar)(const void *, const void *))
{
	QuickSortRec(base, 0, num_elements - 1, size, compar);
}

static void QuickSortRec(void *base, size_t left, size_t right, size_t size, int (*compar)(const void *, const void *))
{
	size_t pivot_index = 0;
	
	if (left < right)
	{	
		pivot_index = Partition(base, left, right, size, compar);
		if (0 != pivot_index)
		{
			QuickSortRec(base, left, pivot_index - 1, size, compar);
		}			
		QuickSortRec(base, pivot_index + 1, right, size, compar);
	}
}

static size_t Partition(void *base, size_t left, size_t right, size_t size, int (*compar)(const void *, const void *))
{
	char *pivot = ((char *)base) + (right * size);
	size_t i = left;
	size_t j = 0;
	
	for (j = left; j < right; ++j)
	{
		if (0 > compar((void *)(((char *)base) + (j * size)), (void *)pivot))
		{
			SwapData(((char *)base) + (i * size), ((char *)base) + (j * size), size);
			++i;
		} 
	}
	
	SwapData(((char *)base) + (i * size), ((char *)base) + (right * size), size);
	
	return i;
}
		
/**************************************************************************************
							Helper Functions
**************************************************************************************/
static int RadixCountingSort(int array[], size_t size, size_t mask)
{
	size_t i = 0;
	
	int *lut = NULL;
	int *base_lut = NULL;
	
	assert(NULL != array);
	
	lut = (int *)calloc(size, sizeof(int));
	if (NULL == lut)
	{
		errno = ENOMEM;
		perror("CountingSort Malloc");
		return FAILURE;
	}
	
	base_lut = (int *)calloc(BASE, sizeof(int));
	if (NULL == lut)
	{
		errno = ENOMEM;
		perror("CountingSort Malloc");
		return FAILURE;
	}
	
	for (i = 0; i < size; ++i)
	{
		++base_lut[(array[i] / mask) % BASE];
	}
	
	for (i = 1; i < BASE; ++i)
	{
		base_lut[i] += base_lut[i - 1];
	}

	for (i = size; i > 0; --i)
	{
		lut[base_lut[(array[i - 1] / mask) % BASE] - 1] = array[i - 1];
		--base_lut[(array[i - 1] / mask) % BASE];
	}
	
	for (i = 0; i < size; ++i)
	{
		array[i] = lut[i];
	}
	
	free(lut);
	free(base_lut);
	
	return SUCCESS;
}

static void SwapInt(int *a, int *b)
{
	int swap_temp = 0;
	
	assert(NULL != a);
	assert(NULL != b);
	
	swap_temp = *a;
	*a = *b;
	*b = swap_temp;
}

static void SwapData(char *a, char *b, size_t size)
{
	char temp = 0;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		temp = *a;
		*a = *b;
		*b = temp;
		
		++a;
		++b;
	}
}	




















