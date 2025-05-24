/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for dynamic vector

*****************************/

#include <stddef.h> /*using - size_t*/
#include <assert.h> /*using - assert*/
#include <string.h> /*using - memset*/
#include <stdlib.h> /*using - malloc, realloc, free*/

#include "../include/vector.h"

#define GROWTH_FACTOR 2
#define REDUCE_RATIO 4
#define REDUCE_FACTOR 2

struct dynamic_vector {

	void *data;
	size_t size;
	size_t capacity;
	size_t element_size;
};


vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = NULL;
	
	assert(0 != capacity);
	assert(0 != element_size);
	
	vector = (vector_t *)malloc(sizeof(vector_t));
	if (NULL == vector)
	{
		/*Allocation failed*/
		return NULL;
	}
	
	vector->data = calloc(capacity, element_size);
	if (NULL == vector->data)
	{
		/*Allocation failed*/
		free(vector);
		return NULL;
	}
	
	vector->capacity = capacity;
	vector->element_size = element_size;
	vector->size = 0;
 
 	return vector;
}


void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	memset(vector->data, 0, vector->size * vector->element_size);
	free(vector->data);
	vector->data = NULL;
	
	memset((void *)vector, 0, sizeof(vector_t));
	free(vector);
	
	vector = NULL;
}
	

int VectorPushBack(vector_t *vector, const void *element)
{	
	int flag = 0;
	assert(NULL != vector);
	assert(NULL != element);
	
	if (vector->size == vector->capacity -1)
	{
		flag = VectorReserve(vector, vector->capacity * GROWTH_FACTOR);
	}
	
	memcpy(((void *)((char *)vector->data + (vector->size * vector->element_size))), element, vector->element_size);
	
	++vector->size;
	
	return flag;
}

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	
	--vector->size;

	if (vector->size <= vector->capacity / REDUCE_RATIO && 1 <= VectorSize(vector))
	{
		/*setting all data that's gonna be free to 0*/
		memset((void *)((char *)vector->data + vector->size * vector->element_size), 0, (vector->capacity - vector->size - 1) * vector->element_size);
		vector->data = realloc(vector->data, (vector->capacity / REDUCE_FACTOR) * vector->element_size);
		vector->capacity /= REDUCE_FACTOR;
	}	
}


int VectorReserve(vector_t *vector, size_t reserve_size)
{
	void *reserve_space = vector->data;
	
	assert(NULL != vector);
	
	if (reserve_size < vector->capacity)
	{
		return 1;
	}
	
	reserve_space = realloc(vector->data, reserve_size * vector->element_size);
	if (NULL == reserve_space)
	{
		return 1;
	}
	
	vector->data = reserve_space;
	vector->capacity = reserve_size;
	
	return 0;
}

int VectorShrinkToSize(vector_t *vector)
{
	int flag = 0;
	void *reserve_space = vector->data;
	
	assert(NULL != vector);
	
	reserve_space = realloc(vector->data, (vector->size + 1) * vector->element_size);
	if (NULL == reserve_space)
	{
		flag = 1;
	}
	
	vector->data = reserve_space;
	vector->capacity = vector->size +1;
	
	return flag;
}



void *VectorGetAccessToElement(const vector_t *vector, size_t index)
{
	assert(NULL != vector);
	/*assert(index <= vector->size);*/
	
	return (void *)((char *)vector->data + (index * vector->element_size));
}


size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	return vector->capacity;
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);
	return vector->size == 0;
}












