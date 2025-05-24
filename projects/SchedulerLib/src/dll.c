/*****************************
	Name : Or Beruven

	Reviewed By : 

	Date Test:

	Description : c file for doubly linked list

*****************************/

#include <stdio.h> /*using - perror*/
#include <stdlib.h> /*using - malloc, free*/
#include <assert.h> /*using - assert*/
#include <errno.h> /*using - errno*/

#include "dll.h"

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
	node_t *prev;
};

struct doubly_linked_list
{
	node_t *head;
	node_t *tail;
};


enum flag {IS_MATCH = 1, ISNT_MATCH = 0};


/************************ Functions ************************/

dll_t *DLLCreate()
{
	dll_t *new_list = (dll_t *) malloc(sizeof(dll_t));
	if (NULL == new_list)
	{
		errno = ENOMEM;
		perror("Allocation Failed\n");
		return NULL;
	}
	
	
	new_list->head = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_list->head)
	{
		errno = ENOMEM;
		perror("Allocation Failed\n");
		free(new_list);
		return NULL;
	}
	
	new_list->tail = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_list->tail)
	{
		errno = ENOMEM;
		perror("Allocation Failed\n");
		free(new_list->tail);
		free(new_list);
		
		return NULL;
	}
	
	DLLSetData(new_list->head, ((void *)new_list)); 
	new_list->head->prev = NULL;
	new_list->head->next = new_list->tail;
	
	DLLSetData(new_list->tail, ((void *)new_list));
	new_list->tail->prev = new_list->head;
	new_list->tail->next = NULL;
	
	return new_list;
}

void DLLDestroy(dll_t *dll)
{
	assert(NULL != dll);
	
	while (!DLLIsEmpty(dll))
	{
		DLLPopFront(dll);
	}
	
	free(dll->head);
	free(dll->tail);
	free(dll);
}

/******************** Iterator Functions ************************/


iterator_t DLLBeginIter(const dll_t *dll)
{
	assert(NULL != dll);
	
	return dll->head->next;
}


iterator_t DLLNextIter(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->next;
}

iterator_t DLLEndIter(const dll_t *dll)
{
	assert(NULL != dll);
	
	return dll->tail;
}

iterator_t DLLPrevIter(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->prev;
}

/******************** add and remove Functions ************************/

iterator_t DLLRemove(iterator_t iterator)
{
	iterator_t to_ret = DLLNextIter(iterator);
	
	assert(NULL != iterator->prev);
	assert(NULL != iterator->next);
	assert(NULL != iterator);
	
	DLLPrevIter(iterator)->next = DLLNextIter(iterator);
	DLLNextIter(iterator)->prev = DLLPrevIter(iterator);

	free(iterator);
	
	return to_ret;
}


iterator_t DLLInsert(iterator_t iterator, void *data)
{
	iterator_t new_node = NULL;
	
	assert(NULL != iterator);
	assert(NULL != data);

	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		errno = ENOMEM;
		perror("Allocation Failed\n");
		
		while (NULL != DLLNextIter(iterator))
		{
			iterator = DLLNextIter(iterator);
		}
		
		return iterator;
	}
	
	DLLSetData(new_node, data);
	new_node->next = iterator;
	new_node->prev = DLLPrevIter(iterator);
	DLLPrevIter(iterator)->next = new_node;
	iterator->prev = new_node;
	
	return new_node;
}
	
	
iterator_t DLLPushBack(dll_t *dll, void *data)
{
	return DLLInsert(DLLEndIter(dll), data);
}	

iterator_t DLLPushFront(dll_t *dll, void *data)
{
	return DLLInsert(DLLBeginIter(dll), data);
}


void *DLLPopBack(dll_t *dll)
{
	void *data_to_ret = NULL;
	assert(NULL != dll);
	
	data_to_ret = DLLGetData(dll->tail->prev);
	
	DLLRemove(DLLPrevIter(DLLEndIter(dll)));
	
	return data_to_ret;
}

void *DLLPopFront(dll_t *dll)
{
	void *data_to_ret = NULL;

	assert(NULL != dll);
	
	data_to_ret = DLLGetData(DLLBeginIter(dll));
	
	DLLRemove(DLLBeginIter(dll));
		
	return data_to_ret;
}


void *DLLGetData(iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->data;
}
	
void DLLSetData(const iterator_t iterator, void *data)
{
	assert(NULL != iterator);
	assert(NULL != data);
	
	iterator->data = data;
}

int DLLIsSameIter(const iterator_t iter1, const iterator_t iter2)
{	
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return iter1 == iter2;
}

int DLLIsEmpty(const dll_t *dll)
{
	assert(NULL != dll);
	
	return (DLLBeginIter(dll) == DLLEndIter(dll));
}


/******************** Traverse Functions**************************/

static int CountFunc(void *data, void *counter)
{
	assert(NULL != counter);
	
	(void)data;
	
	++(*(size_t *)counter);
	
	return 0;
}

size_t DLLCount(const dll_t *dll)
{
	size_t counter = 0;
	action_func_t func = CountFunc;
	
	assert(NULL != dll);
	
	DLLForEach(DLLBeginIter(dll), DLLEndIter(dll), func, (void *)&counter);
	
	return counter;
}
	
	
int DLLForEach(iterator_t from, const iterator_t to, action_func_t user_func, void *param)
{
	int flag = 0;	
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	while (!flag && !DLLIsSameIter(from, to))
	{
		flag = user_func(from->data, param);
		from = DLLNextIter(from);
	}
	
	return flag;
}


iterator_t DLLFind(iterator_t from, iterator_t to, is_match_t user_func, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);

	while (!DLLIsSameIter(from, to) && ISNT_MATCH == user_func(from->data, param))
	{
		from = DLLNextIter(from);
	}
	
	return from;
}

dll_t *DLLMultiFind(dll_t *dll_dest, iterator_t from, iterator_t to, is_match_t user_func, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	while (!DLLIsSameIter(from, to))
	{
		 if (IS_MATCH == user_func(from->data, param))
		 {
		 	DLLPushBack(dll_dest, from->data);
		 }
		 
		from = DLLNextIter(from);
	}
	
	return dll_dest;
}

iterator_t DLLSplice(iterator_t dest, iterator_t src_from ,iterator_t src_to)
{
	iterator_t iter_temp = NULL;
	
	assert(NULL != dest);
	assert(NULL != src_from);
	assert(NULL != src_to);
	
	iter_temp = src_from->prev;
	
	DLLPrevIter(src_from)->next = src_to;
	DLLPrevIter(src_to)->next = dest;
	
	DLLPrevIter(dest)->next = src_from;
	
	src_from->prev = DLLPrevIter(dest);
	
	dest->prev = DLLPrevIter(src_to);
	src_to->prev = iter_temp;

	return dest;
}



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
