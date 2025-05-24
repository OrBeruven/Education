/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h> /*using - perror*/
#include <stdlib.h> /*using - malloc, free*/
#include <assert.h> /*using - assert*/

#include "../include/linked_list.h"

struct Node
{
    void *data;
    node_t *next;
}/*node_t*/;

struct SingleLinkedList
{
	node_t *head;
	node_t *tail;
}/*sll_t*/;

/*typedef node_t *iterator_t;*/

/************************ Functions ************************/

sll_t *SLLCreate()
{
	node_t *dummy = NULL;
	sll_t *new_list = (sll_t *) malloc(sizeof(sll_t));
	if (NULL == new_list)
	{
		perror("Allocation Failed\n");
		return NULL;
	}
	
	
	dummy = (node_t *)malloc(sizeof(node_t));
	if (NULL == dummy)
	{
		perror("Allocation Failed\n");
		free(new_list);
		return NULL;
	}
	
	dummy->data = ((void *)new_list); 
	dummy->next = NULL;
	
	new_list->head = dummy;
	new_list->tail = dummy;
	
	return new_list;
}

/*
void SLLDestroy(sll_t *sll)
{
    iterator_t iter = NULL;
    iterator_t next_iter = NULL;
    
    assert(NULL != sll);
    
    next_iter = sll->head;
    
    while (NULL != next_iter->next)
    {
        iter = next_iter;
        next_iter = next_iter->next;
        free(iter);
    }
    
    free(next_iter);
    free(sll);
}*/


void SLLDestroy(sll_t *sll)
{
	assert(NULL != sll);
	while (!SLLIsEmpty(sll))
	{
		sll->head = SLLRemove(sll->head);
	}
	free(sll->head);
	free(sll);
}

/******************** Iterator Functions ************************/

iterator_t SLLBeginIter(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->head;
}


iterator_t SLLNextIter(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->next;
}

iterator_t SLLEndIter(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->tail;
}



iterator_t SLLRemove(iterator_t iterator)
{
	iterator_t next_iter = NULL;
	
	assert(NULL != iterator);
		
	next_iter = iterator->next;
	
	if (NULL == iterator->next)
	{
		return NULL;
	}
	
	iterator->data = next_iter->data;
	iterator->next = next_iter->next;
	free(next_iter);
	
	if (NULL == iterator->next)
	{
		((sll_t *)iterator->data)->tail = iterator;
	}
	
	return iterator;
}

iterator_t SLLInsertBefore(iterator_t iterator, void *data)
{	
	iterator_t new_node = NULL;
	
	assert(NULL != iterator);
	assert(NULL != data); /*need this?*/

	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		perror("Allocation Failed\n");
		
		while (NULL != iterator->next)
		{
			iterator = iterator->next;
		}
		
		return iterator;
	}
	
	new_node->next = iterator->next;
	new_node->data = iterator->data;
	
	iterator->next = new_node;
	iterator->data = data;
	
	if (NULL == new_node->next)
	{
		((sll_t*)new_node->data)->tail = new_node;
	}
	
	return iterator;
}




void *SLLGetData(iterator_t iterator)
{
	assert(NULL != iterator);
	return iterator->data;
}
	
void SLLSetData(const iterator_t iterator, void *data)
{
	assert(NULL != iterator);
	assert(NULL != data);
	
	iterator->data = data;
}

int SLLIsSameIter(const iterator_t iter1, const iterator_t iter2)
{	
	assert(NULL != iter1);
	assert(NULL != iter2);
	return iter1 == iter2;
}

int SLLIsEmpty(const sll_t *sll)
{
	assert(NULL != sll);
	
	return (NULL == sll->head->next);
}


static int CountFunc(void *data, void *counter)
{
	assert(NULL != counter);
	
	(void)data;
	
	++(*(size_t *)counter);
	
	return 0;
}


size_t SLLCount(const sll_t *sll)
{
	size_t counter = 0;
	action_func func = CountFunc;
	
	assert(NULL != sll);
	
	if (SLLForEach(sll->head, sll->tail, func, (void *)&counter))
	{
		counter = 0;;
	}
	
	return counter;
}
	
	
int SLLForEach(iterator_t from, const iterator_t to, action_func user_func, void *param)
{
	int flag = 0;	
	
	while (!flag && from != to)
	{
		flag = user_func(from, param);
		from = from->next;
	}
	
	return flag;
}


iterator_t SLLFind(iterator_t from, iterator_t to, is_match user_func, void *param)
{
	int is_matching = 0;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	
	is_matching = user_func(from, param);	
	
	while (from != to && !is_matching)
	{
		from = from->next;
		is_matching = user_func(from, param);	
	}
	
	return is_matching ? from : to;
}
	
	
	
sll_t *SLLAppend(sll_t *dest ,sll_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	
	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	
	src->tail->data = (void *)dest;
	
	src->head->next = NULL;
	src->head->data = (void *)src;

	dest->tail = src->tail;
	src->tail = src->head;
	
	return dest;
}
	
	






	
