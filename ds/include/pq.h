/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : header file for Priority Queue

*****************************/

#ifndef __ILRD_OL139_40_PQ_H__
#define __ILRD_OL139_40_PQ_H__

#include <stddef.h> /*size_t*/

typedef struct pq pq_t;

/*
* PQCreate Description:
*	Creates a new Priority Queue.
*	Enqueued element will be sorted according to user's priority func	
*	If priority func is invalied - behavior is undefined
*				 											
* @params:
*	priority_func - Pointer to a compare function
*
* @returns:
*	Pointer to pq. If error occured - returns null.
*
* @Complexity
*	O(1)
*/
pq_t *PQCreate(int (*priority_func)(const void *lhs, const void *rhs));

/*
* PQDestroy Description:
* 	Deallocates a given PQ from memory.
* 
* @params:
*	pq - Pointer to a PQ.
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	None
*
* @Complexity
*	O(n)
*/
void PQDestroy(pq_t *pq);

/*
* PQEnqueue Description:
*	Inserts a new element to an existing PQ.
*
* @params:
*	pq - pointer to a PQ.
* 	if the pointer is invalid - behavior is undefined 
*	data - void pointer to data.
*
* @returns:
*	0 if successful. Otherwise will return a non-zero value.
*
* @Complexity
*	O(n)
*/
int PQEnqueue(pq_t *pq, void *data);

/*
* PQDequeue Description:
*		delete highest priority element in PQ.
*
* @params:
*	pq - pointer to a PQ.
* 	if the pointer is invalid - behavior is undefined 
*
* @returns:
*	none.
*
* @Complexity
*	O(1)
*/
void PQDequeue(pq_t *pq);

/*
* PQPeek Description:
*	returns the data of the front element in a PQ.
*
* @params:
*	pq - pointer to a PQ.
* 	if the pointer is invalid - behavior is undefined.
*
* @returns:
*	void pointer to data.
*
* @Complexity
*	O(1)
*/
void *PQPeek(const pq_t *pq);

/*
* PQIsEmpty Description:
*	check if the pq is empty.
*
* @params:
*	pq - pointer to a PQ.
* 	if the pointer is invalid - behavior is undefined.
*
* @returns:
*	1 if empty, else 0. 
*
* @Complexity
*	O(1)
*/
int PQIsEmpty(const pq_t *pq);

/*
* PQSize Description:
*	returns the amount of elements in the PQ.
* 
* @params:
*	pq - pointer to a PQ.
* 	if the pointer is invalid - behavior is undefined.
*
* @returns:
*	number of elemnets
*
* @Complexity
*	O(n)
*/
size_t PQSize(const pq_t *pq);

/*
* PQErase Description:
*	Finds an element according to parameter given by user and erases it from the PQ.
*
* @params:
*	pq - pointer to a PQ.
* 	if the pointer is invalid - behavior is undefined.
*	is_match_func - boolean function to match by the param.
*	param - pointer to the parameter for comparison
*
* @returns:
*	Pointer to erased data. If the element doesn't exist - will return null. 
*
* @Complexity
*	O(n)
*/
void *PQErase(pq_t *pq, int (*is_match)(const void *data, const void *param), void *param);

/*
* PQClear Description:
*	clears all elements in an existing pq.
*
* @params:
*	pq - pointer to a PQ.
* 	if the pointer is invalid - behavior is undefined.
*
* @returns:
*	none 
*
* @Complexity
*	O(n)
*/
void PQClear(pq_t *pq);

/*
* PQMerge Description:
*	merges source PQ to destination PQ
*
* @params:
*	pq_dest - Pointer to source PQ that will merge to dest
* 	pq_src - Pointer to destination PQ that src will be merged into. After merge, src will be empty.
*	if either of the pointers are invalid - behavior is undefined.
*
* @returns:
*	pointer to the pq_dest. 
*
* @Complexity
*	O(n + m)
*/
pq_t *PQMerge(pq_t *pq_dest, pq_t *pq_src);

#endif
