#ifndef __ILRD_139_40__AVL_H__
#define __ILRD_139_40__AVL_H__
/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 26.03.2023

	Description : h file for AVL Tree

*****************************/
#include <stddef.h>	/* size_t */

typedef struct avl_tree avl_t;

/* The AVL tree uses unique keys only.
Thus, inserting data with a key that already exists in the tree will result in undefined behavior */

typedef enum order
{
	IN_ORDER = 0,
	POST_ORDER = 1,
	PRE_ORDER = 2
}order_t;

/*******************************************************/
/*
* AVLCreate description:
*	Creates a new AVL tree.
*
* @param:
*	cmp_func - pointer to a comparison function.
*	The comparison function must return an integer less than, equal to, or greater than zero,
*	if the first argument is considered to be respectively less than, equal to, or greater than the second.
*	If the pointer to the compare function is invalid, the behavior is undefined.
*
* @return:
*	Returns pointer to the newly created AVL tree.
*	In case of failure - Returns NULL.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
avl_t *AVLCreate(int (*cmp_func)(const void *, const void *));									

/*
* AVLDestroy description:
*	Deallocates the memory space of the AVL tree.
*
* @param:
*	AVL - Pointer to the AVL tree.
* 	If the pointer is invalid - the behavior is undefined
*
* @return:
*	None.
*
* complexity
*	Time: O(n)
*	Space O(n)
*/
void AVLDestroy(avl_t *avl);

/*
* AVLInsert description:
*	Inserts the data into the avl. Performs balancing operation if the AVL tree is unbalanced.
*
* @param:
*	avl - Pointer to the avl.
* 	If the pointer is invalid - the behavior is undefined.
*	data - The data to be inserted.
* 
* @return:
*	returns 0 for success and non-zero value for failure.
*	If the key already exists in the avl, the behavior is undefined.
*
* complexity
*	Time: O(log(n)).
*	Space O(log(n))
*/
int AVLInsert(avl_t *avl, void *data);

/*
* AVLRemove description:
*	Removes the data according to the key received. Performs balancing operation if the AVL tree is unbalanced.
*
* @param:
*	avl - Pointer to the avl.
* 	If the pointer is invalid - the behavior is undefined.
*	key - The key to be removed
* 
* @return:
*	void
*
* complexity
*	Time: O(log(n))
*	Space O(log(n))
*/
void AVLRemove(avl_t *avl, const void *key); 

/*
* AVLFind description:
*	Finds the data according to the key.
*
* @param:
*	avl - Pointer to the avl.
* 	If the pointer is invalid - the behavior is undefined.
*	key - key to find within the AVL.
* 
* @return:
*	Returns void pointer to the data that was found.
*	Returns NULL if there is no match.
*
* complexity
*	Time: O(log(n)).
*	Space O(log(n))
*/
void *AVLFind(const avl_t *avl, const void *key);

/*
* AVLForEach description:
*	Applies user func on every element in the avl.
*
* @param:
*	avl - Pointer to the avl.
*	action_func - pointer to the user action function.
*	param - A parameter for the action function.
* 	If the pointer is invalid for either the AVL or the action function - the behavior is undefined.
*	order - An enum value according to which the traverse is done: pre order, post order and in order
* 
* @return:
*	0 - SUCCESS.
*	non-zero value - IF Function's return is different from 0; 
*
* complexity
*	Time: O(n)
*	Space O(log(n))
*/
int AVLForEach(avl_t *avl, int (*action_func)(void *, void *), void *param, order_t order);

/*
* AVLIsEmpty description:
*	Checks if the AVL is empty. 
*
* @param:
*	AVL - Pointer to the AVL.
* 
* @return:
*	Returns 1 if the AVL is empty or 0 otherwise.
*
* complexity
*	Time: O(1)
*	Space O(1)
*/
int AVLIsEmpty(const avl_t *avl);													

/*
* AVLCount description:
*	Counts the number of keys in the AVL. 
*
* @param:
*	AVL - Pointer to the AVL.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns the number of keys in the AVL.
*
* complexity
*	Time: O(n)
*	Space O(log(n))
*/
size_t AVLCount(const avl_t *avl);

/*
* AVLHeight description:
*	Calculates the height of the AVL.
*
* @param:
*	AVL - Pointer to the AVL.
* 	If the pointer is invalid - the behavior is undefined.
* 
* @return:
*	Returns the height of the AVL.
*
* complexity
*	Time O(log(n)).
*	Space O(log(n)). 
*/
size_t AVLHeight(const avl_t *avl);

/*
advanced:
dll_t *AVLMultiFind(const avl_t *avl, int(*is_match)(const void *, const void *), const void *key, dll_t *dll);  
void AVLRemoveMultiple(avl_t *avl, int(*is_match)(const void *, const void *), const void *param); 
	*/


#endif
