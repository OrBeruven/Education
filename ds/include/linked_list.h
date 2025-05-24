/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : header file for linked list

*****************************/

#ifndef __ILRD_OL139_40_LINKED_LIST_H__
#define __ILRD_OL139_40_LINKED_LIST_H__



typedef struct Node node_t;
typedef node_t *iterator_t;
typedef struct SingleLinkedList sll_t;

/* stops after first failure returns success or failure */
typedef int (*action_func)(void *, void *);
 
typedef int (*is_match)(const void *, const void *);


/***************************** Iterator Functions *************************/

/*
* SLLBeginIter Description:
*	returns an iterator to the start of the linked list
*
* @Params:
*	sll - pointer to the linked list.
*
* @Returns:
*	returns an iterator to the first node
	if "sll" is invalid then the behavior of the function is undefined
*
* @Complexity
*	Time: O(1)
*/
iterator_t SLLBeginIter(const sll_t *sll);


/*
* SLLNextIter Description:
*	returns the iterator that points to the next node.
*
* @Params:
*	iterator - pointer to the current node.
*       if "iterator" is invalid then  the behavior of the function is undefined
*
* @Returns:
*	returns the iterator that points to the next node.
*
* @Complexity
*	Time: O(1)
*/
iterator_t SLLNextIter(const iterator_t iterator);


/*
* SLLEndIter Description:
*	returns the iterator that points to the end of the linked list.
*
* @Params:
*	sll - pointer to the linked list.
*
* @Returns:
*       if "sll" is invalid then  the behavior of the function is undefined
*	returns the iterator that points to the end of the linked list.
*
* @Complexity
*	Time: O(1)
*/
iterator_t SLLEndIter(const sll_t *sll);


/*
* SLLIsSameIter Description:
*	Compares two iterators
*
* @Params:
*	iter1 - iterator points to a node in a linked list.
*	iter2 - iterator points to a node in a linked list.
*
* @Returns:
*	returns 1 if they are equal.
	returns 0 otherwise.
*
* @Complexity
*	Time: O(1)
*/
int SLLIsSameIter(const iterator_t iter1, const iterator_t iter2);


/************************** User Functions ************************/


/*
* Count Description:
*	Counts the number of nodes in the linked list.
*
* @Params:
*	sll - pointer to the  linkedlist.
*
* @Returns:
*	Returns the number of nodes in the linked list.
*	if "sll" is invalid then  - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(N)
*/
size_t SLLCount(const sll_t *sll);


/*
* InsertBefore Description:
*	Insert a node before the node pointed by the given iterator.
*
* @Params:
*	iterator - pointer to the linked list.
*	val - the value for the inserted node.
*
* @Returns:
*	returns the iterator variable to the inserted node.
*        In case of fail returns iterator to the tail node.
*        if "iterator" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(1)
*/
iterator_t SLLInsertBefore(iterator_t iterator, void *data);


/*
* Remove Description:
*	Removes a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator to the node to be removed.
*
* @Returns:
*	returns an iterator to the next node in the linked list.
*       if "iterator" is invalid then - the behavior of the function is undefined
*       Iterator invalidation can occur if the same iterator is used after the function has returned
*	
*
* @Complexity
*	Time: O(1)
*/
iterator_t SLLRemove(iterator_t iterator);


/*
* Find Description:
*	Execute the given function on a given part of the linked list (inclusive 'from' to exclusive 'to') with a given parameter.
*
* @Params:
*	from - pointer to the start of the range in the linked list.
*	to - pointer to the end of the range in the linked list.
*	match_func - pointer to a given compare function.
*	param - paramter to compare to.
*
* @Returns:
*	returns an iterator to the matching node.
*       In case of fail returns iterator to "to".
*       if "iterator" is invalid then - the behavior of the function is undefined
*
* @Complexity
*	Time: O(n)
*/
iterator_t SLLFind(iterator_t from, iterator_t to, is_match user_func, void *param);


/*
* SetData Description:
*	sets the value of a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator points to the node.
*	data - the data to set to the node.
*
* @Returns:
*	void
*
* @Complexity
*	Time: O(1)
*/
void SLLSetData(const iterator_t iterator, void *data);


/*
* GetData Description:
*	gets the value of a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator  points to a node.
*
* @Returns:
*	returns void* to the data
*       if "iterator" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(1)
*/
void *SLLGetData(iterator_t iterator);


/*
* ForEach Description:
*	Execute the given function on a given part of the linked list (inclusive 'from' to exclusive 'to') with a given parameter.
*
* @Params:
*	from - pointer to the start of the range in the linked list.
*	to - pointer to the end of the range in the linked list.
*	action_func - pointer to a given action function sent by user.
*	param - paramter for the action function.
*
* @Returns:
*	returns action_function status. 
*       0 if succeeded. 
*       if one of the operations of the action func fails returns value different from 0.
*       if "iterator" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(n)
*/
int SLLForEach(iterator_t from, const iterator_t to, action_func user_func, void *param);
/*
* IsEmpty Description:
*	Checks if the linked list is empty.
*
* @Params:
*	sll - pointer to the linked list to be checked whether it's empty.
*
* @Returns:
*	1 or 0 if the linked list is empty or not, respectively.
*
* @Complexity
*	Time: O(1)
*/
int SLLIsEmpty(const sll_t *sll);

/*
* Create Description:
*	Creates the linked list.
*
* @Params:
*	sll - pointer to the linked list.
*
* @Returns:
*	pointer to the created linked list.
*	returns NULL if allocation failed
*
* @Complexity
*	Time: O(1)
*/
sll_t *SLLCreate();

/*
* Destroy Description:
*	Destroys the given linked list.
*
* @Params:
*       sll - pointer to the linked list to be removed.
*
* @Returns:
*	void
*        if "sll" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(n)
*/
void SLLDestroy(sll_t *sll);


/*
* SLLAppend Description:
*		group two queue into one big queue where dest is first out.
*		src remains empty queue
*
* @Params:
*		dest - queue pointer to append on
*		src - queue pointer ro add to dest from			
*
* @Returns:
*		returns the queue pointer to dest after append
*        if "dest" and "src" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(1)
*/
sll_t *SLLAppend(sll_t *dest ,sll_t *src);

#endif
