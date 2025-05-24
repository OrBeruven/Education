/*****************************
	Name : Or Beruven

	Reviewed By : Yotam Sasson

	Date Test: 14.02.2023

	Description : c file for c_buffer implementation

*****************************/

#include <stdio.h> /*using - perror*/
#include <stdlib.h> /*using - malloc, free*/
#include <string.h> /*using - memcpy*/
#include <assert.h> /*using - assert*/
#include <errno.h> /*using - errno*/

#include "../include/c_buffer.h"

enum buffer_status {EMPTY = 0, NOT_EMPTY = 1};

struct c_buffer
{
	size_t capacity;
	size_t read;
	size_t write;
	char data[1];
};

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *new_buffer = NULL;
	assert(0 != capacity);
	
	new_buffer = (c_buffer_t *)malloc(sizeof(c_buffer_t) + capacity);
	if (NULL == new_buffer)
	{
		errno = ENOMEM;
		perror("Allocation Error");
		return NULL;
	}
	
	new_buffer->capacity = capacity;
	new_buffer->read = 0;
	new_buffer->write = 0;
	new_buffer->data[capacity] = EMPTY;
	
	return new_buffer;
}

void CBufferDestroy(c_buffer_t *buffer)
{
	assert(NULL != buffer);

	free(buffer);
}


size_t CBufferSize(const c_buffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer->capacity - CBufferFreeSpace(buffer);
}


size_t CBufferFreeSpace(const c_buffer_t *buffer)
{
	size_t to_ret = (buffer->read - buffer->write + buffer->capacity) % buffer->capacity;
	
	assert(NULL != buffer);
	
	return (0 == to_ret && CBufferIsEmpty(buffer)) ? buffer->capacity : to_ret;
}


int CBufferIsEmpty(const c_buffer_t *buffer)
{
	assert(NULL !=buffer);
	
	return (buffer->data[buffer->capacity] == EMPTY);
}


ssize_t CBufferWrite(c_buffer_t *buffer,const void *src, size_t data_size)
{
	size_t bytes_to_write = 0;
	size_t free_space = CBufferFreeSpace(buffer);
	
	assert(NULL != buffer);
	assert(NULL != src);
	assert(0 != data_size);
	
	if (0 == free_space)
	{
		errno = ENOBUFS;
		return -1;
	}
	else if (free_space < data_size)
	{
		data_size = free_space;
	}
	
	bytes_to_write = (buffer->capacity) - buffer->write;
	
	if (bytes_to_write > data_size)
	{
		bytes_to_write = data_size;
	}	
	
	memcpy((&buffer->data[buffer->write]), src, bytes_to_write);
	memcpy((&buffer->data[0]), (char *)src + (sizeof(char) * bytes_to_write), data_size - bytes_to_write);
	
	buffer->write = (buffer->write + data_size) % buffer->capacity;
	
	
	buffer->data[buffer->capacity] = NOT_EMPTY;
	
	return data_size;
}



ssize_t CBufferRead(c_buffer_t *buffer, void *dest, size_t size)
{
	size_t bytes_to_read = 0;
	
	assert(NULL != buffer);
	assert(NULL != dest);
	
	if (CBufferIsEmpty(buffer))
	{
		errno = ENODATA;
		return -1;
	}
	else if (size > CBufferSize(buffer))
	{
		size = CBufferSize(buffer);
	}
	
	
	bytes_to_read = (buffer->capacity) - buffer->read;
	
	if (bytes_to_read > size)
	{
		bytes_to_read = size;
	}	
	
	memcpy(dest, (&buffer->data[buffer->read]), bytes_to_read);
	memcpy((char *)dest + (sizeof(char) * bytes_to_read), (&buffer->data[0]), size - bytes_to_read);
	
	buffer->read = (buffer->read + size) % buffer->capacity;

	buffer->data[buffer->capacity] = buffer->read == buffer->write ? EMPTY : NOT_EMPTY;
	
	return size;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
