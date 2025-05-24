/*****************************
	Name : Or Beruven

	Reviewed By : Oran

	Date Test: 28.02.2023

	Description : c file for Priority Queue

*****************************/

#include <stdio.h> /*perror*/
#include <stdlib.h> /*free, malloc*/
#include <errno.h> /*errno*/
#include <assert.h> /*assert*/

#include "../include/pq_heap.h"
#include "../include/heap.h"

struct pq
{
	heap_t *heap;
};


pq_t *PQCreate(int (*priority_func)(const void *lhs, const void *rhs))
{
	pq_t *new_pq = NULL;
	
	assert(NULL != priority_func);
	
	new_pq = (pq_t *)malloc(sizeof(pq_t));
	
	if (NULL == new_pq)
	{
		errno = ENOMEM;
		perror("Allocation Failed\n");
		return NULL;
	}
	
	new_pq->heap = HeapCreate(priority_func);
	
	if (NULL == new_pq->heap)
	{
		free(new_pq);
		return NULL;
	}
	
	return new_pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->heap);
	
	HeapDestroy(pq->heap);
	pq->heap = NULL;
	
	free(pq);
	pq = NULL;
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	assert(NULL != pq->heap);
	
	return HeapPush(pq->heap, data);
}

void PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->heap);
	
	HeapPop(pq->heap);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->heap);
	
	return HeapPeek(pq->heap);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->heap);
	
	return HeapIsEmpty(pq->heap);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->heap);
	
	return HeapSize(pq->heap);
}

void *PQErase(pq_t *pq, int (*is_match)(const void *data, const void *param), void *param)
{
	void *data = NULL;
	
	assert(NULL != pq);
	assert(NULL != pq->heap);
	assert(NULL != is_match);
	
	data = HeapRemove(pq->heap, is_match, param);
	return data;
}
	
void PQClear(pq_t *pq)
{
	size_t queue_size = 0;
	
	assert(NULL != pq);	
	assert(NULL != pq->heap);
	
	queue_size = HeapSize(pq->heap);
		
	while (0 < queue_size)
	{
		HeapPop(pq->heap);
		--queue_size;
	}
}
	
pq_t *PQMerge(pq_t *pq_dest, pq_t *pq_src)
{
    size_t queue_size = 0;

	assert(NULL != pq_dest);	
	assert(NULL != pq_src);
	assert(NULL != pq_dest->heap);
	assert(NULL != pq_src->heap);

    queue_size = HeapSize(pq_src->heap);
	while (0 < queue_size)
	{
        HeapPush(pq_dest->heap, HeapPeek(pq_src->heap));
		HeapPop(pq_src->heap);
		--queue_size;
	}

	return pq_dest;
}
