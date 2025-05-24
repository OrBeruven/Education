/********************************************
*	Developer:	Nir Davidovitch				*
*	Date:		03/02/2023					*
*	Reviewer:	Aviv						*
********************************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include "../include/vector.h"

struct dynamic_vector {
	void *data;
	size_t size;
	size_t capacity;
};

#define GROWTH_FACTOR ((size_t) 2)
#define SHRINKING_FACTOR ((size_t) 4)

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = NULL;
	
	assert(0 != capacity);
	(void) element_size;
	
	vector = (vector_t *) malloc(sizeof(vector_t));
	if (NULL == vector)
	{
		printf("vector allocation failed!\n");
		return NULL;
	}

	vector->data = malloc(capacity * sizeof(void *));
	if (NULL == vector->data)
	{
		printf("vector's data allocation failed!\n");
		free(vector);
		return NULL;
	}
	
	vector->size = 0;
	vector->capacity = capacity;
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	free(vector->data);
	free(vector);
}

status_t VectorPushBack(vector_t *vector, const void *element)
{
	void **place_to_push = NULL;
	void *tmp = NULL;
	
	assert(NULL != vector);
	assert(NULL != element);
	
	place_to_push = (void **) ((char *) (vector->data) + (vector->size * sizeof(void *)));
	*place_to_push = (void *) element;

	++(vector->size);
	
	if (vector->size == vector->capacity)
	{
		tmp = realloc(vector->data, (vector->capacity * GROWTH_FACTOR) * sizeof(void *));
		if (NULL == tmp)
		{
			printf("Allocating more data failed!\n");
			return FAILURE;
		}
		vector->data = tmp;
		vector->capacity *= GROWTH_FACTOR;
	}
	
	return SUCCESS;
}

void VectorPopBack(vector_t *vector)
{
	void *tmp = NULL;
	
	assert(NULL != vector);
	
	--(vector->size);
	
	if (vector->size <= (vector->capacity / SHRINKING_FACTOR))
	{
		tmp = realloc(vector->data, (vector->capacity / GROWTH_FACTOR) * sizeof(void *));
		if (NULL != tmp)
		{
			vector->data = tmp;
			vector->capacity /= GROWTH_FACTOR;
		}
	}
}

void *VectorGetAccessToElement(const vector_t *vector, size_t index)
{
	assert(NULL != vector);
	
	return (void *) ((char *)vector->data + (index * sizeof(void *)));
}

status_t VectorReserve(vector_t *vector, size_t reserve_size)
{
	void *tmp = NULL;
	
	assert(NULL != vector);
	
	if (vector->capacity >= reserve_size)
	{
		return SUCCESS;
	}
	
	tmp = realloc(vector->data, reserve_size * sizeof(void *));
	if (NULL == tmp)
	{
		perror("\n\033[1;29mSystem:\033[0m Allocating adittional data failed!\n");
		return FAILURE;
	}
	
	vector->data = tmp;
	vector->capacity = reserve_size;
	
	return SUCCESS;
}

status_t VectorShrinkToSize(vector_t *vector)
{
	void *tmp = NULL;
	
	assert(NULL != vector);
	
	tmp = realloc(vector->data, (vector->size + 1) * sizeof(void *));	
	if (NULL == vector->data)
	{
		printf("\n\033[1;29mSystem:\033[0m Allocating adittional data failed!\n");
		return FAILURE;
	}
	
	vector->data = tmp;
	vector->capacity = vector->size + 1;
	
	return SUCCESS;
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (0 == vector->size);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->capacity;
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->size;
}