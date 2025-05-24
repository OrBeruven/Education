/*****************************
	Name : Or Beruven

	Reviewed By : 

	Date Test: 

	Description : header file for c_buffer

*****************************/
#ifndef __ILRD_OL139_40_C_BUFFER_H__
#define __ILRD_OL139_40_C_BUFFER_H__


#include <stddef.h> /*using - size_t*/
#include <sys/types.h> /*using - ssize_t*/

/***********ADT - Circular Buffer Implementation***********/

typedef struct c_buffer c_buffer_t;

/************ Function declerations and descriptions ***************/


/*
* CBufferCreate Description:
* 		Create buffer set to given capacity
*
* @Params:
* 		capacity - the capacity size of the new buffer
*
* @Returns:
* 		pointer to the created buffer.
*		returns NULL if allocation failed and errno is set
*		"Cannot Allocate Memory"
*		if capacity in 0, behavior is undefined
*
* @Complexity
* 		Time: O(1)
*/
c_buffer_t *CBufferCreate(size_t capacity);



/*
* CBufferDestroy Description:
* 		Destroy given buffer
*
* @Params:
* 		buffer - the buffer to be destroyed
*
* @Returns:
* 		void
*		if buffer is invalid pointer - behavior of function is undefined
*
* @Complexity
* 		Time: O(1)
*/
void CBufferDestroy(c_buffer_t *buffer);



/*
* CBufferWrite Description:
* 		Write data to end of buffer
*
* @Params:
* 		buffer - pointer to buffer to write on
*		src - pointer to source data to write from
*		data_size - the size to read from source
*
* @Returns:
* 		returns the number of bytes that has been written, -1 if failed to write
*		and errnor is set to indicate the error. - "No Buffer Space Available".
*		write may transfer fewer than "data_size" bytes.
*		if src or buffer are invalid - behavior of the function is undefined
*
* @Complexity
* 		Time: O(n)
*/
ssize_t CBufferWrite(c_buffer_t *buffer,const void *src, size_t data_size);



/*
* CBufferRead Description:
* 		Read data from the buffer
*
* @Params:
* 		buffer - pointer to buffer to read from
*		dest - pointer to destination to write to
*		data_size - the size to read from buffer
*
* @Returns:
* 		returns the number of bytes that has been written, -1 if failed
*		and errnor is set to indicate the error. - "No Data Available".
*		if dest or buffer are invalid - behavior of the function is undefined
*		if dest doesnt have enough allocation, could cause segmentaion fault
*
* @Complexity
* 		Time: O(n)
*/
ssize_t CBufferRead(c_buffer_t *buffer, void *dest, size_t size);



/*
* CBufferSize Description:
* 		Returns the current size of data in bytes in given buffer
*
* @Params:
* 		buffer - pointer to buffer to get size from
*
* @Returns:
* 		returns the current size in bytes
*		if buffer pointer is invalid - behavior of function is undefined
*
* @Complexity
* 		Time: O(1)
*/
size_t CBufferSize(const c_buffer_t *buffer);



/*
* CBufferFreeSpace Description:
* 		Returns the size of free space in bytes in given buffer
*
* @Params:
* 		buffer - pointer to buffer to get free space from
*
* @Returns:
* 		returns the free space available in bytes
*		if buffer pointer is invalid - behavior of function is undefined
*
* @Complexity
* 		Time: O(1)
*/
size_t CBufferFreeSpace(const c_buffer_t *buffer);



/*
* CBufferIsEmpty Description:
* 		Returns whether buffer is empty or not
*
* @Params:
* 		buffer - pointer to buffer
*
* @Returns:
* 		returns 1 if buffer is empty, else returns 0
*		if buffer pointer is invalid - behavior of function is undefined
*
* @Complexity
* 		Time: O(1)
*/
int CBufferIsEmpty(const c_buffer_t *buffer);

/**Advanced**/
c_buffer_t *CBufferResize(c_buffer_t *buffer, size_t new_capacity);															/*O(n)*/
ssize_t CBufferOverwrite(c_buffer_t *buffer,const void *src, size_t data_size); /*Write element to end of buffer*/			/*O(n)*/



#endif
