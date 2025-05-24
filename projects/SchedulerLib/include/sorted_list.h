/*****************************
	Name : Or Beruven

	Reviewed By : Tomer

	Date Test: 20.2.2023

	Description : h file for sorted linked list

*****************************/
#ifndef __ILRD_OL139_40_SORTED_H__
#define __ILRD_OL139_40_SORTED_H__

#include <stddef.h>

#include "dll.h"

typedef struct sol_iterator sol_iterator_t;
typedef struct sorted_linked_list sol_t;

struct sol_iterator
{
	iterator_t DLLiterator;
	
	#ifndef NDEBUG
	dll_t *dll;
	#endif
};

typedef int (*cmp_func_st)(const void *data1, const void *data2);


/*
* SortedListCreate description:
* Creates a sorted List. 
* The list is sorted according to a compare function 'user_func'.
*
* @param:
* user_func - pointer to a compare function which adheres to the temlpate 'int user_func(const void *data1, const void *data2)'
* 
* @return:
* Returns a pointer to the created sorted linked list.
*
* complexity
* O(1)
*
*/
sol_t *SortedListCreate(cmp_func_st user_func);

/*
* SortedListDestroy description:
* Destroys sorted linked list
*
* @param:
* sol - Pointer to a sorted linked list
* 
* @return
* void
*
* complexity
* O(n)
*
*/
void SortedListDestroy(sol_t *sol);

/*
* SortedListIsEmpty description:
* Check if list is empty
*
* @param:
* sol - Pointer to a sorted linked list
* 
* @return:
* Returns 1 if empty, 0 if not
*
* complexity
* O(1)
*
*/
int SortedListIsEmpty(const sol_t *sol);

/*
* SortedListSize description:
* Returns number of elements in the list
*
* @param:
* sol - Pointer to a sorted linked list
* 
* @return:
* Returns number of elements in linked list
*
* @Complexity
* O(n)
*
*/							
size_t SortedListSize(const sol_t *sol);

/*
* SortedListInsert Description:
*	Inserts a node to the list in its sorted place.
*
* @Params:
*	sol - Pointer to a sorted linked list
*	data - pointer to the value for the inserted node.
*
* @Returns:
*	returns the iterator variable to the inserted node.
*	In case of failure returns iterator to the tail node.
*	if 'sol' is invalid, the behavior of the function is undefined.
*
* @Complexity
*	Time: O(n)
*/
sol_iterator_t SortedListInsert(sol_t *sol, void *data); /*reuse Find*/

/*
*  SortedListRemove Description:
*	Removes a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator to the node to be removed.
*
* @Returns:
*	returns an iterator to the next node in the sorted linked list.
*   if "iterator" is invalid, the behavior of the function is undefined
*   Iterator invalidation can occur if the same iterator is used after the function has returned
*	
* @Complexity
*	Time: O(1)
*/
sol_iterator_t SortedListRemove(sol_iterator_t iterator);

/*
*  SortedListPopBack Description:
*  	Removes the last node in the list and returns a pointer to the data saved in removed node
*
* @Params:
*	sol - Pointer to a sorted linked list
*
* @Returns:
*	returns pointer to data in removed node
*	
* @Complexity
*	Time: O(1)
*/
void *SortedListPopBack(sol_t *sol);

/*
*  SortedListPopFront Description:
*  	Removes the first node in the list and returns a pointer to the data saved in removed node
*
* @Params:
*	sol - Pointer to a sorted linked list
*
* @Returns:
*	returns pointer to data in removed node
*	
* @Complexity
*	Time: O(1)
*/
void *SortedListPopFront(sol_t *sol);

/*
* SortedListFindIf Description:
*	searches the sorted list according to is_match_st function in the selected range (inclusive 'from' to exclusive 'to') with a given parameter.
*
* @Params:
*	from - pointer to the start of the range in the sorted linked list.
*	to - pointer to the end of the range in the sorted linked list.
*	match_func - pointer to a given is_match_st function.
*	param - paramter to find.
*
* @Returns:
*	returns an iterator to the first matching node.
*   In case of fail returns iterator to "to".
*   if "iterator" is invalid, the behavior of the function is undefined
*
* @Complexity
*	Time: O(n)
*/
sol_iterator_t SortedListFindIf(sol_iterator_t from, sol_iterator_t to, is_match_t user_func, void *param); 

/*
* SortedListFind Description:
*	Searches the sorted list according to the cmp_func in 'sol' in the selected range (inclusive 'from' to exclusive 'to') with a given parameter.
*
* @Params:
*	from - pointer to the start of the range in a sorted linked list.
*	to - pointer to the end of the range in a sorted linked list.
*	sol - Pointer to a sorted linked list
*	to_find - paramter to compare.
*
* @Returns:
*	returns an iterator to the first matching node.
*   In case of fail returns iterator to "to".
*   if "iterator" is invalid, the behavior of the function is undefined
*
* @Complexity
*	Time: O(n)
*/
sol_iterator_t SortedListFind(sol_t *sol, sol_iterator_t from, sol_iterator_t to, const void *to_find);

/*
* SortedListForEach Description:
*	Execute the given action_func_st on a given range of the sorted list (inclusive 'from' to exclusive 'to') with a given parameter.
*
* @Params:
*	from - pointer to the start of the range in the linked list.
*	to - pointer to the end of the range in the linked list.
*	action_func - pointer to a given action function sent by user.
*	param - paramter for the action function.
*
* @Returns:
*	returns action_function status. 
*   0 if succeeded. 
*   if one of the operations of the action func fails returns value different from 0.
*   if "iterator" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(n)
*/
int SortedListForEach(sol_iterator_t from, sol_iterator_t to, action_func_t user_func, void *param); /*assert from to*/
	
/*
* SortedListGetData Description:
*	gets the value of a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator  points to a node.
*
* @Returns:
*	returns void* to the data
*   if "iterator" is invalid then - the behavior of the function is undefined.
*	of foreach changes the values of data, the list may not be sorted.
*
* @Complexity
*	Time: O(1)
*/																					
void *SortedListGetData(sol_iterator_t iterator);

/*
* SortedListBeginIter Description:
* returns the iterator that points to first node of the sorted list.
* if list is empty, returns tail node.
*
* @Params:
*	sol - pointer to the sorted list.
*
* @Returns:
*	returns an iterator to the first node
*	if "sol" is invalid then the behavior of the function is undefined
*
* @Complexity
*	Time: O(1)
*/																									
sol_iterator_t SortedListBeginIter(const sol_t *sol);	
	
/*
* SortedListEndIter Description:
*	returns the iterator that points to the a dummy node at the end of the sorted list.
*
* @Params:
*	sol - pointer to the sorted list.
*
* @Returns:
*   if "sol" is invalid then the behavior of the function is undefined
*	returns the iterator that points to the end of the linked list.
*
* @Complexity
*	Time: O(1)
*/																								
sol_iterator_t SortedListEndIter(const sol_t *sol);

/*
* SortedListNextIter Description:
*	returns the iterator that points to the next node.
*
* @Params:
*	iterator - pointer to the current node.
*   if "iterator" is invalid then  the behavior of the function is undefined
*
* @Returns:
*	returns the iterator that points to the next node.
*
* @Complexity
*	Time: O(1)
*/																						
sol_iterator_t SortedListNextIter(sol_iterator_t iterator);	
												
/*
* SortedListPrevIter Description:
*	returns the iterator that points to the previous node.
*
* @Params:
*	iterator - pointer to the current node.
*   if "iterator" is invalid then  the behavior of the function is undefined
*
* @Returns:
*	returns the iterator that points to the next node.
*
* @Complexity
*	Time: O(1)
*/																		
sol_iterator_t SortedListPrevIter(sol_iterator_t iterator);	

/*
* SortedListIsSameIter Description:
*	Compares two iterators
*
* @Params:
*	iter1 - iterator points to a node in a sorted list.
*	iter2 - iterator points to a node in a sorted list.
*
* @Returns:
*	returns 1 if they are equal.
	returns 0 otherwise.
*
* @Complexity
*	Time: O(1)
*/																	
int SortedListIsSameIter(sol_iterator_t iter1, sol_iterator_t iter2);	

/*
* SortedListMerge Description:
*	Combines two sorted lists into one sorted list, sorted according to the same inherent compare function.
*	Lists must be sorted according to the same compare function.
*	src_list will be emptied but not destroyed.
*
* @Params:
*	dest_sol - pointer to a sorted list the two lists will merge to.
*	src_sol - pointer to a sorted list to be merged with dest_sol.
*
* @Returns:
*	returns pointer to dest_sol.
	incase two lists are not sorted according to the same compare function the behavior is undefined.
*
* @Complexity
*	Time: O(n+m)
*/																				
sol_t *SortedListMerge(sol_t *dest_sol, sol_t *src_sol);																		

#endif
