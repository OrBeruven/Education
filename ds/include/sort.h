/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : h file for sort algorithms

*****************************/

#ifndef __ILRD_OL139_40_SORT_H__
#define __ILRD_OL139_40_SORT_H__

#include <stddef.h>		/* size_t */
#include <sys/types.h>	/* ssize_t*/


/*
* BubbleSort Description:
* Sorts the array using the "Bubble Sort" method
*
* @Params:
*  	array - The array to be sorted
*  	size - The size of the array to be sorted
*	cmp_func - A pointer to the compare function
*
* @Returns:
* 	none
*
* @Complexity
* 	Time: O(n^2)
*	Space: O(1)
*/
void BubbleSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs));

/*
* InsertionSort Description:
* Sorts the array using the "Insertion Sort" method
*
* @Params:
*  	array - The array to be sorted
*  	size - The size of the array to be sorted
*	cmp_func - A pointer to the compare function
*
* @Returns:
* 	none
*
* @Complexity
* 	Time: O(n^2)
*	Space: O(1)
*/
void InsertionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs));

/*
* SelectionSort Description:
* Sorts the array using the "Selection Sort" method
*
* @Params:
*  	array - The array to be sorted
*  	size - The size of the array to be sorted
*	cmp_func - A pointer to the compare function
*
* @Returns:
* 	none
*
* @Complexity
* 	Time: O(n^2)
*	Space: O(1)
*/
void SelectionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs));

/*
* CountingSort Description:
* Sorts the array using the "Counting Sort" method
*
* @Params:
*      array - The array to be sorted
*      size - The size of the array to be sorted
*
* @Returns:
*     dynamic allocation - success or failure
*
* @Complexity
*     Time: O(n + k)
*    Space: O(k)
*
*   k is the difference between the largest and smallest elements
*/
int CountingSort(int array[], size_t size);

/*
* RadixSort Description:
* Sorts the array using the "Radix Sort" method
*
* @Params:
*      array - The array to be sorted
*      size - The size of the array to be sorted
*
* @Returns:
*     dynamic allocation - success or failure
*
* @Complexity
*     Time: O(n * k)
*    Space: O(n)
*    
*    k is the number of digits in the largest element 
*/
int RadixSort(int array[], size_t size);


/*
*
* @description: 
* 	Perform a binary search on an array of integers to find the index of a given number
* @params:
*    arr: a pointer to a sorted array of integers
*        if the array isn't sorted, the result is undifined
*
*	size: a size_t representing the size of the array
*	num: a size_t representing the number to search for
* @return: 
*	ssize_t - the index of the number in the array, or -1 if it is not found
*
* @complexity:
*	time - O(log n)
*	space - O(lod n)
*/

ssize_t BinarySearchIterative(int *arr, size_t size, int num);
ssize_t BinarySearchRecursive(int *arr, size_t size, int num);

/*
*
* @description: 
* 	Perform a merge sort on an array of integers
* @params:
*	arr_to_sort: a pointer to an array of integers to sort
*	num_elements: a size_t variable representing the number of elements in the array
* @return: 
*	int - 0 if the function executed successfully, non-zero otherwise
* @complexity:
*	time - O(nlog n)
*	space - O(n)
*/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*
*
* @description: 
* 	Perform a quick sort on an array of elements
* @params:
*	base: a pointer to the base of the array to be sorted
*	num_elements: the number of elements in the array
*	size: the size of each element in the array in bytes
*	compar: a function pointer that takes two const void pointers as 
*			arguments and returns an integer less than, equal to, or 
*			greater than zero if the first argument is considered to 
*			be respectively less than, equal to, or greater than the second
* @return: 
*	none
*	time - O(n^2) - amortized O(nlog n)
*	space - O(log n)
*/
void Qsort(void *base, size_t num_elements, size_t size, int (*compar)(const void *, const void *));


#endif
