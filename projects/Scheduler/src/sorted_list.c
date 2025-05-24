/*****************************
	Name : Or Beruven

	Reviewed By : Tomer

	Date Test: 20.2.2023

	Description : c file for sorted linked list

*****************************/

#include <stdlib.h>/*free, malloc*/
#include <stdio.h>/*perror*/
#include <errno.h> /*errno*/
#include <assert.h>/*assert*/

#include "sorted_list.h"

#define MATCH_TRUE 1
#define MATCH_FALSE 0
#define ARE_EQUAL 0

typedef struct wrapper wrapper_t;

struct sorted_linked_list
{
	dll_t *list;
	cmp_func_st user_func;
};

struct wrapper
{
	cmp_func_st cmp;
	void *param;
};

/*********************Static Functions **********************/

static int CompToIsMatch(const void *data1, const void *bundle);
static int IsBiggerCmp(const void *data_from_node, const void *arg);

/************************ Functions ************************/

sol_t *SortedListCreate(cmp_func_st user_func)
{
	sol_t *new_sol = NULL;
	
	assert(NULL != user_func);
	
	new_sol = (sol_t *)malloc(sizeof(sol_t));
	if (NULL == new_sol)
	{
		errno = ENOMEM;
		perror("Allocation Failed\n");
		return NULL;
	}
	
	new_sol->list = DLLCreate();
	if (NULL == new_sol->list)
    {
   		free(new_sol);
		errno = ENOMEM; 
        perror("Memory allocation:");
        return NULL;
    }
	
	new_sol->user_func = user_func;
	
	return new_sol;
}

void SortedListDestroy(sol_t *sol)
{
	assert(NULL != sol);
	
	DLLDestroy(sol->list);
	sol->list = NULL;
	
	free(sol);
	sol = NULL;
}

sol_iterator_t SortedListFindIf(sol_iterator_t from, sol_iterator_t to, is_match_t user_func, void *param)
{
	assert(NULL != user_func);
	assert(NULL != from.DLLiterator);
	assert(NULL != to.DLLiterator);
	
	#ifndef NDEBUG
	assert(NULL != from.dll);
	assert(NULL != to.dll);
	assert(from.dll == to.dll);
	#endif
	
	from.DLLiterator = DLLFind(from.DLLiterator, to.DLLiterator, user_func, param);
	
	return from;
}	
	
sol_iterator_t SortedListFind(sol_t *sol, sol_iterator_t from, sol_iterator_t to, const void *to_find)
{
	wrapper_t wrp = {NULL};
	
	assert(NULL != sol);
	assert(NULL != from.DLLiterator);
	assert(NULL != to.DLLiterator);
	
	#ifndef NDEBUG
	assert(NULL != from.dll);
	assert(NULL != to.dll);
	assert(from.dll == to.dll);
	#endif
	
	wrp.cmp = sol->user_func;
	wrp.param = (void *)to_find;
	
	from.DLLiterator = DLLFind(from.DLLiterator, to.DLLiterator, CompToIsMatch, &wrp);
	
	return from;
}
	
	

int SortedListIsEmpty(const sol_t *sol)
{
	assert(NULL != sol);
	
	return DLLIsEmpty(sol->list);
}

size_t SortedListSize(const sol_t *sol)
{
	assert(NULL != sol);
	
	return DLLCount(sol->list);
}


sol_iterator_t SortedListInsert(sol_t *sol, void *data)
{
	wrapper_t wrp = {NULL};
	sol_iterator_t iter = {NULL};
	
	assert(NULL != sol);
	
	
	wrp.cmp = sol->user_func;
	wrp.param = data;
	
	iter = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), IsBiggerCmp, &wrp);
	
	#ifndef NDEBUG
	iter.dll = sol->list;
	#endif
	
	iter.DLLiterator = DLLInsert(iter.DLLiterator, data);

	return iter;
}


sol_iterator_t SortedListRemove(sol_iterator_t iterator)
{
	assert(NULL != iterator.DLLiterator);
	assert(NULL != DLLNextIter(iterator.DLLiterator));
	assert(NULL != DLLPrevIter(iterator.DLLiterator));
	
	iterator.DLLiterator = DLLRemove(iterator.DLLiterator);
	return iterator;
}


void *SortedListPopBack(sol_t *sol)
{
	assert(NULL != sol);
	return DLLPopBack(sol->list);
}
	
void *SortedListPopFront(sol_t *sol)
{
	assert(NULL != sol);
	
	return DLLPopFront(sol->list);
}


int SortedListForEach(sol_iterator_t from, sol_iterator_t to, action_func_t user_func, void *param)
{
	#ifndef NDEBUG
	assert(NULL != from.dll);
	assert(NULL != to.dll);
	assert(to.dll == from.dll);
	#endif
	
	assert(NULL != from.DLLiterator);
	assert(NULL != to.DLLiterator);
	assert(NULL != user_func);
	
	return DLLForEach(from.DLLiterator, to.DLLiterator, user_func, param);
}

void *SortedListGetData(sol_iterator_t iterator)
{
	assert(NULL != iterator.DLLiterator);
	
	return DLLGetData(iterator.DLLiterator);
}

sol_iterator_t SortedListBeginIter(const sol_t *sol)
{
	sol_iterator_t iter = {NULL};
	
	assert(NULL != sol);
	
	#ifndef NDEBUG
	iter.dll = sol->list;
	#endif
	
	iter.DLLiterator = DLLBeginIter(sol->list);
	
	return iter;
}

sol_iterator_t SortedListEndIter(const sol_t *sol)
{	
	sol_iterator_t iter = {NULL};
	
	assert(NULL != sol);
	
	#ifndef NDEBUG
	iter.dll = sol->list;
	#endif
	
	iter.DLLiterator = DLLEndIter(sol->list);
	
	return iter;
}

sol_iterator_t SortedListNextIter(sol_iterator_t iterator)
{	
	assert(NULL != iterator.DLLiterator);
	
	iterator.DLLiterator = DLLNextIter(iterator.DLLiterator);
	return iterator;
}

sol_iterator_t SortedListPrevIter(sol_iterator_t iterator)
{
	assert(NULL != iterator.DLLiterator);
	
	iterator.DLLiterator = DLLPrevIter(iterator.DLLiterator);
	return iterator;
}

int SortedListIsSameIter(sol_iterator_t iter1, sol_iterator_t iter2)
{
	assert(NULL != iter1.DLLiterator);
	assert(NULL != iter2.DLLiterator);
	
	#ifndef NDEBUG
	assert(iter2.dll == iter1.dll);
	#endif
	
	return DLLIsSameIter(iter1.DLLiterator, iter2.DLLiterator);
}		



sol_t *SortedListMerge(sol_t *dest_sol, sol_t *src_sol)
{
	sol_iterator_t to_dest = {NULL};
	sol_iterator_t to_src = {NULL};
	sol_iterator_t runner_dest = {NULL};
	sol_iterator_t runner_src = {NULL};
	sol_iterator_t temp = {NULL};
	
	assert(NULL != dest_sol);
	assert(NULL != src_sol);
	
	to_dest = SortedListEndIter(dest_sol);
	to_src = SortedListEndIter(src_sol);
	runner_dest = SortedListBeginIter(dest_sol);
	runner_src = SortedListBeginIter(src_sol);
	
	while (!SortedListIsSameIter(runner_src, to_src) && !SortedListIsSameIter(runner_dest, to_dest))
	{
		if (ARE_EQUAL <= dest_sol->user_func(SortedListGetData(runner_dest), 
			SortedListGetData(runner_src)))
		{
			temp = runner_src;
			
			while (ARE_EQUAL <= dest_sol->user_func(SortedListGetData(runner_dest), 
					SortedListGetData(runner_src)) && !SortedListIsSameIter(runner_src, to_src))
			{
				runner_src = SortedListNextIter(runner_src);
			}
			
			DLLSplice(runner_dest.DLLiterator, temp.DLLiterator, runner_src.DLLiterator);
		}
		else
		{
			runner_dest = SortedListNextIter(runner_dest);
		}
	}
	
	if (MATCH_FALSE == SortedListIsEmpty(src_sol))
	{
		DLLSplice(to_dest.DLLiterator, runner_src.DLLiterator, to_src.DLLiterator);
	}
	
	return dest_sol;
}




static int CompToIsMatch(const void *data, const void *wrapper)
{
	const wrapper_t *wrp = (wrapper_t *)wrapper;
	cmp_func_st func;
	assert(NULL != wrp);

	func = wrp->cmp;

	return !(func(data, wrp->param));
}

static int IsBiggerCmp(const void *data, const void *wrapper)
{
	const wrapper_t *wrp = (wrapper_t *)wrapper;
	cmp_func_st func;
	assert(NULL != wrapper);

	func = wrp->cmp;

	return (func(data, wrp->param) > 0);
}





























