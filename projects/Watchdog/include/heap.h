/*****************************
	Name : Green Team

	Reviewed By : Alex

	Date Test: now

	Description : h file for binary heap

*****************************/
#ifndef __ILRD_139_40__HEAP_H__
#define __ILRD_139_40__HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;

/* 
* HeapCreate description:
*	Creates a new binary heap.
*
* @param:
*   cmp_func - compare function, to evaluate elements location inside the heap
*   The type of the heap (Max/Min) will be determine by the cmp_func

* @return:
*	Returns pointer to the newly created binary heap.
*	In case of failure - Returns NULL.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
heap_t *HeapCreate(int (*cmp_func)(const void *, const void *));	

/*
* HeapDestroy description:
*	Deallocates the memory space of the binary heap.
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined
*
* @return:
*	None.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
void HeapDestroy(heap_t *heap);

/*
* HeapPush description:
*	pushes the data into the heap.
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined.
*	data - The data to be inserted.
* 
* @return:
*    Returns success or failure.
*
* complexity
*	Time: O(log n).
*	Space O(1)
*/
int HeapPush(heap_t *heap, void *data);

/*
* HeapPop description:
*	Removes the data at the root of the heap. 
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	none
*
* complexity
*	Time: O(log n) 
*	Space O(1)
*/
void HeapPop(heap_t *heap); 

/*
* HeapPeek description:
*	Returns the data at the root of the heap.
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	A pointer to the element stored in first index. 
*
* complexity
*	Time: O(1).
*	Space O(1)
*/
void *HeapPeek(const heap_t *heap);

/*
* HeapSize description:
*	returns the size of the heap in the current state
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*   Returns the number of occupied elements in heap.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
size_t HeapSize(const heap_t *heap);

/*
* HeapIsEmpty description:
*	Checks if the heap is empty. 
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns 1 if the heap is empty or 0 otherwise.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
int HeapIsEmpty(const heap_t *heap);

/*
* HeapRemoveByKey description:
*	Removes the element from the heap and returns its value.
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined.
*   data - the data of the element to be removed.
* 
* @return:
*	Returns a pointer to the data of the removed element,
*
* complexity
*	Time: O(log n)
*	Space O(1)
*/													
void *HeapRemoveByKey(heap_t *heap, void *data);

/*
* HeapRemove description:
*	Removes the element from the heap and returns its value.
*
* @param:
*	heap - Pointer to the heap.
* 	If the pointer is invalid - the behavior is undefined.
*   data - the data of the element to be removed.
* 
* @return:
*	Returns a pointer to the data of the removed element,
*
* complexity
*	Time: O(log n)
*	Space O(1)
*/													
void *HeapRemove(heap_t *heap, int (*is_match)(const void *, const void *), void *param);

void PrintHeap(heap_t *heap);
void PrintHeapTree(heap_t *heap);

#endif
