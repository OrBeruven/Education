/******************************
	developer: Adir O.
	reviewer: 
	date: 06.03.23
******************************/

#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc, free*/

#include "fsa.h"

/*********************************************************/
#define GREEN_OUT_PUT printf("\033[0;32m");
#define RED_OUT_PUT printf("\033[0;31m");
#define NORMAL_OUT_PUT printf("\033[0m");
#define RESULT_STATUS(STATUS ,EXPECTED_STATUS) {\
		if ((STATUS) == (EXPECTED_STATUS))\
		{\
			GREEN_OUT_PUT\
			printf("Success\n");\
			NORMAL_OUT_PUT\
		}\
		else\
		{\
			RED_OUT_PUT\
			printf("Failure\n");\
			NORMAL_OUT_PUT\
		}\
	}
/*********************************************************/

void TestSuggestSize(void);
void TestInitCount(void);
void TestNotAligned(void);


/*********************************************************/

int main(void)
{
	TestSuggestSize();
	TestInitCount();
	TestNotAligned();
	
	return 0;
}

/*********************************************************/

void TestSuggestSize(void)
{
	size_t block_size1 = 16;
	size_t block_size2 = 12;
	size_t block_size3 = 1;
	size_t num_blocks1 = 5;
	size_t num_blocks2 = 5;
	size_t num_blocks3 = 10;	
	size_t sugg_size1 = FSASuggestSize(num_blocks1, block_size1);
	size_t sugg_size2 = FSASuggestSize(num_blocks2, block_size2);
	size_t sugg_size3 = FSASuggestSize(num_blocks3, block_size3);
	
	printf("\nTesting SuggestSize\n");
	RESULT_STATUS((size_t)88 == sugg_size1, 1);
	RESULT_STATUS(sugg_size1 == sugg_size2, 1);
	RESULT_STATUS(sugg_size1 == sugg_size3, 1);
}
	
void TestInitCount(void)
{
	size_t block_size = 8;
	size_t num_of_blocks = 5;
	size_t segment_size = FSASuggestSize(num_of_blocks, block_size);
	void *pool = malloc(segment_size);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	void *block6 = NULL;
	
	printf("\nTesting Init and Count\n");
	pool = FSAInit(pool, segment_size, block_size);
	RESULT_STATUS(5 == FSACountFree(pool), 1);
	
	block1 = FSAAlloc(pool);
	block2 = FSAAlloc(pool);
	
	*(int *)block1 = 10;
	*(size_t *)block2 = 1;
	
	printf("\nTesting Alloc\n");
	RESULT_STATUS(3 == FSACountFree(pool), 1);
	RESULT_STATUS(1 == *(size_t *)block2, 1);
	
	block3 = FSAAlloc(pool);
	block4 = FSAAlloc(pool);
	block5 = FSAAlloc(pool);
	block6 = FSAAlloc(pool);
	
	*(int *)block3 = 0;
	*(int *)block4 = 0;
	*(int *)block5 = 0;
	
	printf("\nTesting if we get NULL when all blocks are used\n");	
	RESULT_STATUS(NULL == block6, 1);
	RESULT_STATUS(0 == FSACountFree(pool), 1);
	
	printf("\nTesting Free\n");	
	FSAFree(pool, block1);
	FSAFree(pool, block3);
	FSAFree(pool, block4);
	RESULT_STATUS(3 == FSACountFree(pool), 1);
	
	printf("\nTesting second round of Alloc\n");	
	block3 = FSAAlloc(pool);
	block1 = FSAAlloc(pool);
	RESULT_STATUS(1 == FSACountFree(pool), 1);	
	
	free(pool);
}

void TestNotAligned(void)
{
	size_t block_size = 12;
	size_t num_of_blocks = 5;
	size_t segment_size = FSASuggestSize(num_of_blocks, block_size);
	void *pool1 = malloc(segment_size);
	void *pool2 = (char *)pool1 + 4;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	
	printf("\nAnother round of Testing for un-aligned pool\n");
	printf("\nTesting Init and Count\n");
	pool2 = FSAInit(pool2, segment_size - 4, block_size);
	RESULT_STATUS(4 == FSACountFree(pool2), 1);

	block1 = FSAAlloc(pool2);
	block2 = FSAAlloc(pool2);
	
	*(int *)block1 = 10;
	*(size_t *)block2 = 1;
	
	printf("\nTesting Alloc\n");
	RESULT_STATUS(2 == FSACountFree(pool2), 1);
	RESULT_STATUS(1 == *(size_t *)block2, 1);
	
	block3 = FSAAlloc(pool2);
	block4 = FSAAlloc(pool2);
	block5 = FSAAlloc(pool2);
	
	*(int *)block3 = 0;
	*(int *)block4 = 0;
	
	printf("\nTesting if we get NULL when all blocks are used\n");	
	RESULT_STATUS(NULL == block5, 1);
	RESULT_STATUS(0 == FSACountFree(pool2), 1);
	
	printf("\nTesting Free\n");	
	FSAFree(pool2, block1);
	FSAFree(pool2, block3);
	FSAFree(pool2, block4);
	RESULT_STATUS(3 == FSACountFree(pool2), 1);	

	
	free(pool1);
}
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
