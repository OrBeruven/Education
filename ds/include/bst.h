/*****************************
	Name : Or Beruven

	Reviewed By : Oran

	Date Test: 22.3.2023

	Description : h file for Binary Search Tree

*****************************/

#ifndef __ILRD_139_40__BST_H__
#define __ILRD_139_40__BST_H__

#include <stddef.h>	/* size_t */

typedef struct bst_node bst_node_t;
typedef bst_node_t *bst_iter_t;
typedef struct binary_search_tree bst_t;

/* The binary search tree uses unique keys only.
Thus, inserting data with a key that already exists in the tree will cause an undefined behavior */

/*******************************************************/

/*
* BSTCreate description:
*	Creates a new binary search tree.
*
* @param:
*	cmp_func - pointer to a comparison function.
*	The  comparison function must return an integer less than, equal to, or greater than zero,
*	if the first argument is considered to be	respectively less than, equal to, or greater than the second.
*	If the pointer to the compare function is invalid, the behavior is undefined.
*
* @return:
*	Returns pointer to the newly created binary search tree.
*	In case of failure - Returns NULL.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
bst_t *BSTCreate(int (*cmp_func)(const void *, const void *));									

/*
* BSTDestroy description:
*	Deallocates the memory space of the binary search tree.
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined
*
* @return:
*	None.
*
* complexity
*	Time: O(n)
*	Space O(1)
*/
void BSTDestroy(bst_t *bst);

/*
* BSTInsert description:
*	Inserts the data into the bst.
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined.
*	data - The data to be inserted.
* 
* @return:
*    Returns iterator to the newly inserted data.
*    In case of failure - returns EndIter.
*	If the key already exists in the bst, the behavior is undefined.
*
* complexity
*	Time: O(n), Amortized O(log(n)).
*	Space O(1)
*/
bst_iter_t BSTInsert(bst_t *bst, void *data);

/*
* BSTRemove description:
*	Removes the data pointed by the received iterator. 
*
* @param:
*	iter - iterator to the data to be removed.
* 	If iter is invalid - the behavior is undefined.
* 
* @return:
*	none
*
* complexity
*	Time: O(log n) 
*	Space O(1)
*/
void BSTRemove(bst_iter_t iter);

/*
* BSTFind description:
*	Finds the data according to the key.
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined.
*	key - key to find within the bst.
* 
* @return:
*	Returns an iterator to the data which is equal to the key.
*	Returns NULL if there is no match.
*
* complexity
*	Time: O(n), Amortized O(log(n)).
*	Space O(1)
*/
bst_iter_t BSTFind(const bst_t *bst, const void *key); 	

/*
* BSTForEach description:
*	Applies user func on the data in the range `from` (inclusive) to `to` (exclusive).
*
* @param:
*	bst - Pointer to the bst.
*	action_func - pointer to the user action function.
*	param - A parameter for the action function.
* 	If the pointer is invalid for either the bst or the action function - the behavior is undefined.
* 
* @return:
*   Returns action_func return value:    
*   0 upon success.
*   if one of the operations of the action func fails the function will return a non-zero value.
*
* complexity
*	Time: O(n)
*	Space O(1)
*/
int BSTForEach(bst_iter_t from, const bst_iter_t to, int (*action_func)(void *, void *), void *param);

/*
* BSTIsEmpty description:
*	Checks if the bst is empty. 
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns 1 if the bst is empty or 0 otherwise.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
int BSTIsEmpty(const bst_t *bst);													

/*
* BSTSize description:
*	Counts the number of keys in the bst. 
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns the number of keys in the bst.
*
* complexity
*	Time: O(n)
*	Space O(1)
*/
size_t BSTSize(const bst_t *bst);

/*
* BSTGetData description:
*	Gets the data of the key pointed by the received iterator.
*
* @param:
*	iter - iterator to the key whose data is requested.
* 	If the iterator is invalid - the behavior is undefined.
* 
* @return:
*	Returns the data of the given key.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
void *BSTGetData(bst_iter_t iter);

/*
* BSTHeight description:
*	Calculates the maximum levels of the bst.
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns the maximum levels of the bst.
*
* complexity
*	Time: O(n)
*	Space O(n). Amortized O(log(n))
*/
size_t BSTHeight(const bst_t *bst);	/* Recursive solution is allowed */

/********** Iterator Functions **********/																																									

/*
* BSTBeginIter description:
*	Returns an iterator to the first element in an In-Order traversal.
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns an iterator to the first element in an In-Order traversal.
*	In case the bst is empty, returns an invalid iterator representing the end of the bst.
*
* complexity
*	Time: O(n). Amortized O(log(n))
*	Space O(1)
*/
bst_iter_t BSTBeginIter(const bst_t *bst);																																												

/*
* BSTEndIter description:
*	Returns an invalid iterator representing the end of the bst.
*
* @param:
*	bst - Pointer to the bst.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns an invalid iterator representing the end of the bst.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
bst_iter_t BSTEndIter(const bst_t *bst);																			

/*
* BSTNextIter description:
*	Returns the next key, according to In-Order traversal.
*
* @param:
*	iter - iterator to a key in the bst.
* 	If the iterator is invalid - the behavior is undefined.
* 
* @return:
*	Returns iterator to the next key according to In-Order traversal.
*
* complexity
*	Time: O(log(n)), Amortized O(1)
*	Space O(1)
*/																							
bst_iter_t BSTNextIter(const bst_iter_t iter);																																								

/*
* BSTPrevIter description:
*	Returns the previous key, according to In-Order traversal.
*
* @param:
*	iter - iterator to a key in the bst.
* 	If the iterator is invalid - the behavior is undefined.
* 
* @return:
*	Returns iterator to the previous key according to In-Order traversal.
*
* complexity
*	Time: O(log(n)), Amortized O(1)
*	Space O(1)
*/				
bst_iter_t BSTPrevIter(const bst_iter_t iter);																																								

/*
* BSTIsSameIter description:
*	Compares between the two recieved iterators. 
*
* @param:
*	iter1 - iterator to a key in the bst.
*	iter2 - iterator to a key in the bst.
* 	If either iter1 or iter2 are invalid - the behavior is undefined.
* 
* @return:
*	Returns 1 if the iters are the same or 0 otherwise.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/		
int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2);																	

#endif
