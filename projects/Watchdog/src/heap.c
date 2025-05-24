/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 13.04.2023

	Description : c file for Hash Table implemantation

*****************************/
#include <stdio.h>  /*perror*/
#include <stdlib.h> /*malloc, free*/
#include <errno.h>  /*errno, ENOMEM*/
#include <assert.h> /*assert*/

#include "../include/heap.h"
#include "../include/vector.h"

#define INIT_CAPACITY (3)
#define INIT_ELEMENT_SIZE (sizeof(void *))

#define LEFT_CHILD(i) ((2 * (i)) + 1)
#define RIGHT_CHILD(i) ((2 * (i)) + 2)
#define PARENT(i) (((i) - 1) / 2)
#define TOP_INDEX (0)
#define BOTTOM_INDEX (VectorSize(heap->vec) - 1)

#define FAIL (1)
#define SUCCESS (0)

/*******************************************************************************
						Managerial Structure
*******************************************************************************/
struct heap 
{
	vector_t *vec;
    int (*cmp_func)(const void *, const void *);
};


/*******************************************************************************
						Help function declarations
*******************************************************************************/
static void HeapifyUp(heap_t *heap, size_t index);

static void HeapifyDown(heap_t *heap, size_t index);

static void *GetData(heap_t *heap, size_t index);

static void SwapPointers(vector_t *vec, size_t index1, size_t index2);

static int CompareIndexInVec(heap_t *heap, size_t index1, size_t index2);
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						API Function Implementation
*******************************************************************************/
heap_t *HeapCreate(int (*cmp_func)(const void *, const void *))
{
    heap_t *new_heap = NULL;

    assert(NULL != cmp_func);

    new_heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == new_heap)
    {
        errno = ENOMEM;
        perror("HeapCreate");
        return NULL;
    }

    new_heap->vec = VectorCreate(INIT_CAPACITY, INIT_ELEMENT_SIZE);
    if (NULL == new_heap->vec)
    {
        free(new_heap);
        return NULL;
    }
    new_heap->cmp_func = cmp_func;

    return new_heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    VectorDestroy(heap->vec);
    free(heap);
}

int HeapPush(heap_t *heap, void *data)
{
    int status = 0;

    assert(NULL != heap);

    status = VectorPushBack(heap->vec, data);

    HeapifyUp(heap, BOTTOM_INDEX);

    return status;
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return *(void **)VectorGetAccessToElement(heap->vec, TOP_INDEX);
}

size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorSize(heap->vec);
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorIsEmpty(heap->vec);
}

void HeapPop(heap_t *heap)
{
    assert(NULL != heap);

    SwapPointers(heap->vec, TOP_INDEX, BOTTOM_INDEX);
    VectorPopBack(heap->vec);
    HeapifyDown(heap, 0);
}

void *HeapRemove(heap_t *heap, int (*is_match)(const void *, const void *), void *param)
{
    void *to_ret = NULL;
    size_t index = 0;
    size_t size = 0;

    assert(NULL != heap);
    assert(NULL != is_match);

    size = VectorSize(heap->vec);

    while (index < size && 1 != is_match(GetData(heap, index), param))
    {
        ++index;
    }
    
    if (index < size)
    {
        SwapPointers(heap->vec, index, BOTTOM_INDEX);
        to_ret = GetData(heap, BOTTOM_INDEX);
        VectorPopBack(heap->vec);
        if (1 < size)
        {
            HeapifyDown(heap, index);
        }
    }
    
    return to_ret;
}

void *HeapRemoveByKey(heap_t *heap, void *data)
{
    void *to_ret = NULL;
    size_t index = 0;
    size_t size = 0;

    assert(NULL != heap);

    size = VectorSize(heap->vec);

    while (index < size && 0 != heap->cmp_func(GetData(heap, index), data))
    {
        ++index;
    }

    if (index < size)
    {
        SwapPointers(heap->vec, index, BOTTOM_INDEX);
        to_ret = GetData(heap, BOTTOM_INDEX);
        VectorPopBack(heap->vec);
        HeapifyDown(heap, index);
    }

    return to_ret;
}
/*******************************************************************************
*******************************************************************************/

static void HeapifyUp(heap_t *heap, size_t index)
{
    void *element = VectorGetAccessToElement(heap->vec, index);
    void *parent_element = VectorGetAccessToElement(heap->vec, PARENT(index));

    while (index != 0 && 0 <= heap->cmp_func(*(void **)element, *(void **)parent_element))
    {
        SwapPointers(heap->vec, index, PARENT(index));
        index = PARENT(index);
        element = VectorGetAccessToElement(heap->vec, index);
        parent_element = VectorGetAccessToElement(heap->vec, PARENT(index));
    }
}

static void HeapifyDown(heap_t *heap, size_t index)
{
    if ( (LEFT_CHILD(index) < HeapSize(heap)) && (0 <  CompareIndexInVec(heap, LEFT_CHILD(index), index)))
    {
        SwapPointers(heap->vec, LEFT_CHILD(index), index);
        HeapifyDown(heap, LEFT_CHILD(index));
    }
    
    if ( (RIGHT_CHILD(index) < HeapSize(heap)) && (0 <  CompareIndexInVec(heap, RIGHT_CHILD(index), index)))
    {
        SwapPointers(heap->vec, RIGHT_CHILD(index), index);
        HeapifyDown(heap, RIGHT_CHILD(index));
    }
}   

static void *GetData(heap_t *heap, size_t index)
{
    return *(void **)VectorGetAccessToElement(heap->vec, index);
}

static void SwapPointers(vector_t *vec, size_t index1, size_t index2)
{
    void **lhs = VectorGetAccessToElement(vec, index1);
    void **rhs = VectorGetAccessToElement(vec, index2);
    void *temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

static int CompareIndexInVec(heap_t *heap, size_t index1, size_t index2)
{
    return (heap->cmp_func(*(void **)VectorGetAccessToElement(heap->vec, index1), *(void **)VectorGetAccessToElement(heap->vec, index2)));
}