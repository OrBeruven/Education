/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 13.04.2023

	Description : header file for Fixed Size Queue

*****************************/
#ifndef __ILRD__OL139_140_FIXED_SIZE_QUEUE__
#define __ILRD__OL139_140_FIXED_SIZE_QUEUE__

#include <stddef.h> /*size_t*/

#define PEEK_ERROR (99999999)

typedef struct fixed_size_queue fsq_t;

/*
* FSQCreate description:
* Creates a new Fixed Size Queue.
*
* @param:
*   capacity - Number of integer elemnts held at the queue.
*
* @return:
*   Returns pointer to the newly created fsq.
*   In case of failure, returns NULL.
*
* complexity:
* Time: O(1)
* Space O(1)
*/
fsq_t *FSQCreate(size_t capacity);

/*
* FSQDestroy description:
* Destroys a new Fixed Size Queue.
*
* @param:
*   fsq - the queue to be destroyed.
*
* @return:
*   void.
*
* complexity:
* Time: O(1)
* Space O(1)
*/
void FSQDestroy(fsq_t *fsq);

/*
* FSQEnqueue description:
*   Enqueue an element to the end of the queue.
*
* @param:
*   fsq - the queue to add the element to.
*   element - integer element to enqueue to the queue, by value
*
* @return:
*   Returns 0 on success. and non zero on failure (queue is full).
*
* complexity:
* Time: O(1)
* Space O(1)
*/
int FSQEnqueue(fsq_t *fsq, int element);

/*
* FSQDequeue description:
*   Dequeue an element from the front of the queue.
*
* @param:
*   fsq - the queue to remove element from.
*
* @return:
*   void
*
* complexity:
* Time: O(n)
* Space O(1)
*/
void FSQDequeue(fsq_t *fsq);

/*
* FSQDequeue description:
*   Returns the first element, which is front in queue.
*
* @param:
*   fsq - the queue to return element from .
*
* @return:
*   integer by value of the oldest element in queue
*	in case of faulure, returns macro PEEK_ERROR, which is 8 9's : (999999999)
*
* complexity:
* Time: O(1)
* Space O(1)
*/
int FSQPeek(fsq_t *fsq);

/*
* FSQIsEmpty description:
*   Check whether the queue is empty or not
*
* @param:
*   fsq - the queue to check if it's empty .
*
* @return:
*   integer 1 if queue is empty, 0 if not
*
* complexity:
* Time: O(1)
* Space O(1)
*/
int FSQIsEmpty(fsq_t *fsq);


#endif