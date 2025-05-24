/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h> /*using - printf*/

#include "../include/vector.h"

static void IsEmptyTest(vector_t *vector)
{
	(void)vector;
	VectorIsEmpty(vector) ? printf("Success!\n") : printf("Failure!\n");
}

static void IsntEmptyTest(vector_t *vector)
{
	(void)vector;
	VectorIsEmpty(vector) ? printf("Failure!\n") : printf("Success!\n");
}

static void SizeTest(vector_t *vector, size_t size)
{
	(void)vector;
	(void)size;
	VectorSize(vector) == size ? printf("Success!\n") : printf("Failure!\n");
}

static void CapacityTest(vector_t *vector, size_t capacity)
{
	(void)vector;
	(void)capacity;
	VectorCapacity(vector) == capacity ? printf("Success!\n") : printf("Failure!\n");
}

static void GetAccessTest(void *element, double num)
{
	if (*(double *)element == num)
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}
}

static void PopBackTest(vector_t *vector)
{
	/*	current capacity = 8
		current size = 4	*/
	
	VectorPopBack(vector);
	CapacityTest(vector, 8);
	SizeTest(vector, 3);
	
	VectorPopBack(vector);	
	CapacityTest(vector, 4);
	SizeTest(vector, 2);

 	
	VectorPopBack(vector);	
	CapacityTest(vector, 2);
	SizeTest(vector, 1);
}
	
void MainTest(void)
{
	double num = 3;
	void *curr_element = NULL;
	vector_t *vector = VectorCreate(4, 8);
	
	
	printf("Testing VectorIsEmpty :\n");
	IsEmptyTest(vector);
	
	VectorPushBack(vector, (void *)&num);
	num = 4;
	VectorPushBack(vector, (void *)&num);
	
	IsntEmptyTest(vector);
	printf("\n\n");
	
	printf("Testing VectorSize : \n");
	SizeTest(vector, 2);
	num = 5;
	VectorPushBack(vector, (void *)&num);
	SizeTest(vector, 3);
	printf("\n\n");	
	
	printf("Testing VectorCapacity : \n");
	CapacityTest(vector, 4);
	num = 6;
	VectorPushBack(vector, (void *)&num);	
	CapacityTest(vector, 8);	
	printf("\n\n");	
	
	printf("Testing VectorGetAccess : \n");	
	curr_element = VectorGetAccessToElement(vector, 0);
	GetAccessTest(curr_element, 3);
	
	curr_element = VectorGetAccessToElement(vector, 2);
	GetAccessTest(curr_element, 5);
	
	
	curr_element = VectorGetAccessToElement(vector, 3);
	GetAccessTest(curr_element, 6);
	printf("\n\n");	
	
	printf("Testing VectorPopBack : \n");			
	PopBackTest(vector);
	printf("\n\n");


	VectorDestroy(vector);
}
	
	

int main(void)
{
	MainTest();
	
	return 0;
}
