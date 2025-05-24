/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel Wurtzel 		*
*	Date      : 11/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */

#include "vsa.h"

#define WORD_SIZE (sizeof(void *))

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE  	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

static void InitTest();
static void LargestChunkAvailableTest();
static void AllocTest();
static void FreeTest();
static void DeFragTest();

/***********************************************/

int main()
{
	InitTest();

	LargestChunkAvailableTest();

	AllocTest();

	FreeTest();
	
	DeFragTest();
	
	

	return 0; 
}

static void InitTest()
{
	vsa_t *vsa = NULL;
	size_t segment_size = 160;
	char *pool = (char *)malloc(segment_size); 
	
	vsa = VSAInit(pool, segment_size);
	printf(U_LINE"\nTesting VSAInit:\n\n"RESET);
	
	PRINT_TEST(NULL != vsa);
	PRINT_TEST(pool == (char *)vsa);
	
	free(pool);
	
	printf("Testing if not aligned:\n");
	pool = (char *)malloc(segment_size);
	vsa = VSAInit((pool + 2), segment_size);
	PRINT_TEST(pool + WORD_SIZE == (char *)vsa);
	
	NEW_LINE;
	
	free(pool);
}

static void LargestChunkAvailableTest()
{
	vsa_t *vsa = NULL;
	size_t segment_size = 64;
	size_t largest_chunk = 0;
	void *memory_pool_ptr = NULL;
	
	memory_pool_ptr = malloc(segment_size);
	
	printf(U_LINE"Test vsa Largest Chunk Available:\n\n"RESET);
	
	vsa = VSAInit(memory_pool_ptr, segment_size);
	
	largest_chunk = VSALargestChunkAvailable(vsa);
	PRINT_TEST(largest_chunk == segment_size - (2 * WORD_SIZE));
	
	free(memory_pool_ptr);
}

static void AllocTest()
{
	vsa_t *vsa = NULL;
	size_t segment_size = 64;
	char *alloc1 = NULL;
	char *alloc2 = NULL;
	char *alloc3 = NULL;
	char *alloc4 = NULL;
	size_t size_block_1 = 8;
	size_t size_block_2 = 16;
	size_t size_block_3 = 2;
	size_t size_block_4 = 2;
	
	char *pool = (char *)malloc(segment_size);
	
	printf(U_LINE"\nTesting VSAAlloc:\n\n"RESET);
	vsa = VSAInit(pool, segment_size);
	alloc1 = (char *)VSAAlloc(vsa, size_block_1);
	PRINT_TEST((char *)vsa + (2 * WORD_SIZE) == alloc1);
	alloc2 = (char *)VSAAlloc(vsa, size_block_2);
	PRINT_TEST(NULL != alloc2);
	PRINT_TEST((2 * WORD_SIZE) == alloc2 - alloc1);
	alloc3 = (char *)VSAAlloc(vsa, size_block_3);
	PRINT_TEST(NULL != (void *)alloc3);
	alloc4 = (char *)VSAAlloc(vsa, size_block_4);
	PRINT_TEST(NULL == (void *)alloc4);
	
	free(pool);
}


static void FreeTest()
{
	vsa_t *vsa = NULL;
	size_t segment_size = 72;
	char *alloc2 = NULL;
	char *alloc4 = NULL;
	size_t size_block_1 = 8;
	size_t size_block_2 = 16;
	size_t size_block_3 = 2;
	size_t size_block_4 = 2;
	
	char *pool = (char *)malloc(segment_size); 
	
	printf(U_LINE"\nTesting VSAFree:\n\n"RESET);
	vsa = VSAInit(pool + 2, segment_size);
	(char *)VSAAlloc(vsa, size_block_1);
	alloc2 = (char *)VSAAlloc(vsa, size_block_2);
	(char *)VSAAlloc(vsa, size_block_3);
	alloc4 = (char *)VSAAlloc(vsa, size_block_4);
	PRINT_TEST(NULL == (void *)alloc4);
	
	printf("free:\n");
	VSAFree(alloc2);
	alloc4 = (char *)VSAAlloc(vsa, size_block_4);
	PRINT_TEST(alloc4 == alloc2);	
	
	free(pool);
}

static void DeFragTest()
{
	vsa_t *vsa = NULL;
	size_t segment_size = 64;
	char *alloc2 = NULL;
	char *alloc3 = NULL;
	char *alloc4 = NULL;
	size_t size_block_1 = 8;
	size_t size_block_2 = 16;
	size_t size_block_3 = 8;
	size_t size_block_4 = 32;
	
	char *pool = (char *)malloc(segment_size); 
	
	printf(U_LINE"\nTesting VSADeFrag:\n\n"RESET);
	vsa = VSAInit(pool, segment_size);
	(char *)VSAAlloc(vsa, size_block_1);
	alloc2 = (char *)VSAAlloc(vsa, size_block_2);
	alloc3 = (char *)VSAAlloc(vsa, size_block_3);
	alloc4 = (char *)VSAAlloc(vsa, size_block_4);
	
	VSAFree(alloc2);
	PRINT_TEST(size_block_2 == VSALargestChunkAvailable(vsa));
	VSAFree(alloc3);
	PRINT_TEST((size_block_2 + size_block_3 + WORD_SIZE) == VSALargestChunkAvailable(vsa));
	alloc4 = (char *)VSAAlloc(vsa, size_block_4);
	PRINT_TEST(NULL != alloc4);
	PRINT_TEST(alloc2 == alloc4);
	PRINT_TEST(0 == VSALargestChunkAvailable(vsa));
	
	free(pool);
}

