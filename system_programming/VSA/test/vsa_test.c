/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 12.03.2023

	Description : c file for vsa tests

*****************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h> /*system, malloc, free*/
#include <errno.h>	/*errno*/

#include "utilities.h"
#include "vsa.h"


/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void InitTest(void);

static void AllocTest(void);

static void FreeTest(void);

static void LargestChunckTest(void);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	HEADER(Testing CreateDestroy);
	InitTest();
	printf("\n");
	
	HEADER(Testing Alloc);
	AllocTest();
	printf("\n");
	
	HEADER(Testing Free and Defragmentation);
	FreeTest();
	printf("\n");

	HEADER(Testing Largest Chucnk Available);
	LargestChunckTest();
	printf("\n");
	

	return 0;
}


/*******************************************************************************
						Test function definitions
*******************************************************************************/
static void InitTest(void)
{
	void *mem = NULL;
	vsa_t *vsa = NULL;
	
	mem = malloc(32);
	
	RESULT_STATUS(NULL == vsa, 1, Unanitialized);
	
	vsa = VSAInit(mem, 32);
	
	RESULT_STATUS((size_t)vsa == (size_t)mem, 1, SameAddress);
	RESULT_STATUS(NULL == vsa, 0, Initialized);
	
	free(mem);
}

static void AllocTest(void)
{
	void *segment = malloc(101);
	vsa_t *vsa = VSAInit(segment, 101);
	void *alloc = NULL;
	void *alloc2 = NULL;
	void *alloc3 = NULL;
		
	errno = 0;	
	
	alloc = VSAAlloc(vsa, 16);
	alloc2 = VSAAlloc(vsa, 8);
	alloc3 = VSAAlloc(vsa, 8);
	
	
	RESULT_STATUS(NULL != alloc, 1, Initialized);
	RESULT_STATUS(NULL != alloc2, 1, );
	RESULT_STATUS(NULL != alloc3, 1, );
	
	alloc = VSAAlloc(vsa, 36);
	RESULT_STATUS((ENOMEM == errno), 1, Errno ENOMEM);
	RESULT_STATUS((NULL == alloc), 1, );
	
	
	alloc = VSAAlloc(vsa, 6);
	RESULT_STATUS((NULL != alloc), 1, );
	RESULT_STATUS(((char*)alloc - (char*)alloc3 - 8) == 8, 1, Offset);
	
	vsa = VSAInit(segment, 101);
	
	errno = 0;	
	
	alloc = VSAAlloc(vsa, 16);
	alloc2 = VSAAlloc(vsa, 8);
	alloc3 = VSAAlloc(vsa, 8);
	
	
	RESULT_STATUS(NULL != alloc, 1, Adjust);
	RESULT_STATUS(NULL != alloc2, 1, );
	RESULT_STATUS(NULL != alloc3, 1, );
	
	alloc = VSAAlloc(vsa, 36);
	RESULT_STATUS((ENOMEM == errno), 1, Errno ENOMEM);
	RESULT_STATUS((NULL == alloc), 1, );
	
	
	alloc = VSAAlloc(vsa, 6);
	RESULT_STATUS((NULL != alloc), 1, );
	RESULT_STATUS(((char*)alloc - (char*)alloc3 - 8) == 8, 1, );

	free(segment);
}

static void FreeTest(void)
{
	void *mem = NULL;
	vsa_t *vsa = NULL;
	void *alloc = NULL;
	void *alloc2 = NULL;
	void *alloc3 = NULL;
	void *alloc4 = NULL;
	
	errno = 0;
	
	mem = malloc(100);
	
	vsa = VSAInit(mem, 32);
	RESULT_STATUS((NULL == alloc), 1, );
	alloc = VSAAlloc(vsa, 24);
	RESULT_STATUS((ENOMEM == errno), 1, Errno ENOMEM);
	
	vsa = VSAInit(mem, 72);
	
	alloc = VSAAlloc(vsa, 24);
	alloc2 = VSAAlloc(vsa, 16);
	
	RESULT_STATUS(((size_t)alloc - (size_t)vsa), 16, Offsets);
	RESULT_STATUS(((size_t)alloc2 - (size_t)vsa), 48, );
	
	alloc3 = VSAAlloc(vsa, 1);
	RESULT_STATUS((ENOMEM == errno), 1, Errno ENOMEM);
	RESULT_STATUS((NULL == alloc3), 1, );
	errno = 0;
	
	VSAFree(alloc);
	alloc3 = VSAAlloc(vsa, 1);
	RESULT_STATUS((0 == errno), 1, After Freed Space);
	RESULT_STATUS((NULL != alloc3), 1, );
	RESULT_STATUS(((size_t)alloc3 - (size_t)vsa), 16, );
	
	vsa = VSAInit(mem, 100);
	alloc = VSAAlloc(vsa, 8);
	alloc2 = VSAAlloc(vsa, 8);
	alloc3 = VSAAlloc(vsa, 16);
	
	alloc4 = VSAAlloc(vsa, 32);
	RESULT_STATUS((ENOMEM == errno), 1, Errno ENOMEM);
	RESULT_STATUS((NULL == alloc4), 1, );
	errno = 0;
	
	VSAFree(alloc3);
	
	alloc4 = VSAAlloc(vsa, 32);
	RESULT_STATUS((NULL == alloc4), 0, );
	
	alloc3 = VSAAlloc(vsa, 16);
	RESULT_STATUS((ENOMEM == errno), 1, Errno ENOMEM);
	RESULT_STATUS((NULL == alloc3), 1, );
	errno = 0;
	
	VSAFree(alloc2);
	VSAFree(alloc);
	
	alloc3 = VSAAlloc(vsa, 16);
	RESULT_STATUS((NULL == alloc3), 0, );
	
	free(mem);
}

static void LargestChunckTest(void)
{
	void *mem = NULL;
	vsa_t *vsa = NULL;
	void *alloc = NULL;
	
	errno = 0;
	
	mem = malloc(103);
	
	vsa = VSAInit(mem, 105);
	
	RESULT_STATUS(VSALargestChunkAvailable(vsa), 88, FreeSpace);
	
	alloc = VSAAlloc(vsa, 88);
	RESULT_STATUS(NULL != alloc, 1, );
	
	RESULT_STATUS(VSALargestChunkAvailable(vsa), 0, );
	
	VSAFree(alloc);
	RESULT_STATUS(VSALargestChunkAvailable(vsa), 88, );
	
	alloc = VSAAlloc(vsa, 10);
	RESULT_STATUS(VSALargestChunkAvailable(vsa), 64, );
	
	alloc = VSAAlloc(vsa, 10);
	RESULT_STATUS(VSALargestChunkAvailable(vsa), 40, );
	
	free(mem);
}






