/*****************************
	Name : Or Beruven

	Reviewed By : Harel

	Date Test: 13.2.2023

	Description : header file for Queue

*****************************/


#include <stddef.h> /*using - size_t*/

 
typedef struct queue queue_t; 


/***************************************/


/*
* CreateQueue Description:
* 		Creates the queue.
*
* @Params:
* 		None
*
* @Returns:
* 		pointer to the created queue.
*		returns NULL if allocation failed
*
* @Complexity
* 		Time: O(1)
*/
queue_t *QueueCreate(void);




/*
* DestroyQueue Description:
* 		Destroys the given linked list.
*
* @Params:
*       queue - pointer to the queue to be removed.
*
* @Returns:
* 		void
*       if "queue" is invalid then - the behavior of the function is undefined.
*
* @Complexity
* 		Time: O(n)
*/
void QueueDestroy(queue_t *queue);



/*
* EnQueue Description:
* 		Adds an element to the queue.
*
* @Params:
* 		queue - pointer to the queue.
*		data - pointer to the data to be added to queue
*
* @Returns:
* 		returns 0 if success, or 1 if failure
*		if "queue" is invalid then - the behavior of the function is undefined.
*
* @Complexity
* 		Time: Amortized O(1) 
*/
int QueueEnqueue(queue_t *queue, void *data);


/*
* DeQueue Description:
* 		Removes an element from the queue.
*
* @Params:
* 		queue - pointer to the queue.
*
* @Returns:
* 		No return value.
*		if called for an empty queue behavior is undefined
*
* @Complexity
* 		Time: O(1)
*/
void QueueDequeue(queue_t *queue);

/*
* QueuePeekFront Description:
* 		Returns the value of element currently in top position of queue.
*
* @Params:
* 		queue - pointer to the queue.
*		if "queue" is invalid or empty - the behavior of the function is undefined.
*
* @Returns:
* 		Void pointer to data.
*
* @Complexity
* 		Time: O(1)
*/
void *QueuePeek(const queue_t *queue);

/*
* QueueIsEmpty Description:
* 		Checks if given queue is empty.
*
* @Params:
* 		queue - pointer to the queue.
*
* @Returns:
* 		Returns 1 if queue is empty, 0 if not.
*		if "queue" is invalid or empty - the behavior of the function is undefined.
*
* @Complexity
* 		Time: O(1)
*/
int QueueIsEmpty(const queue_t *queue);

/*
* QueueSize Description:
* 		Returns number of elements in queue.
*
* @Params:
* 		queue - pointer to the queue.
*
* @Returns:
* 		Returns the number of elements in queue.
*		if "queue" is invalid or empty - the behavior of the function is undefined.
*
* @Complexity
* 		Time: O(n)
*/
size_t QueueSize(const queue_t *queue); 

/*
* QueueAppend Description:
* 		Appends queue to another given queue.
*
* @Params:
* 		dest - pointer to the queue.
* 		src - Pointer to a queue to append to first queue.
*
* @Returns:
* 		returns pointer to dest 
*		if "dest" or "src" are invalid or empty - the behavior of the function is undefined.
*
* @Complexity
* 		Time: O(1)
*/
queue_t *QueueAppend(queue_t *dest, queue_t *src);


















