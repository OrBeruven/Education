/*****************************
	Name : Or Beruven

	Reviewed By : Daniel

	Date Test: 07.03.2023

	Description : c file for fsa tests

*****************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h> /*system, malloc, free*/
#include <errno.h>	/*errno*/

#include "utilities.h"
#include "fsa.h"


/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void InitTest(void);

static void AllocTest(void);

static void FreeTest(void);

static void CountFreeTest(void);

static void SuggestSizeTest(void);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	printf("Testing CreateDestroy\n");
	InitTest();
	printf("\n");
	
	printf("Testing Alloc\n");
	AllocTest();
	printf("\n");
	
	printf("Testing Free\n");
	FreeTest();
	printf("\n");
		
	printf("Testing Count Free\n");
	CountFreeTest();
	printf("\n");
	
	printf("Testing Suggest Size\n");
	SuggestSizeTest();
	printf("\n");

	return 0;
}


/*******************************************************************************
						Test function definitions
*******************************************************************************/
static void InitTest(void)
{
	void *mem = NULL;
	fsa_t *fsa = NULL;
	
	mem = malloc(32);
	
	RESULTSTATUS(NULL == fsa, 1);
	
	fsa = FSAInit(mem, 32, 8);
	
	RESULTSTATUS((size_t)fsa == (size_t)mem, 1);
	RESULTSTATUS(NULL == fsa, 0);
	
	free(mem);
}

static void AllocTest(void)
{
	void *mem = NULL;
	fsa_t *fsa = NULL;
	void *alloc = NULL;
	void *alloc2 = NULL;
	
	errno = 0;
	
	mem = malloc(32);
	
	fsa = FSAInit(mem, 32, 8);
	RESULTSTATUS(NULL == alloc, 1);
	
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(NULL == alloc, 0);
	RESULTSTATUS(((size_t)alloc - (size_t)fsa), 8);
	
	alloc2 = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc2 - (size_t)fsa), 16);
	free(mem);
	
	mem = malloc(72);
	
	fsa = FSAInit(mem, 72, 16);
	
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc - (size_t)fsa), 8);
	
	alloc2 = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc2 - (size_t)fsa), 24);
	
	free(mem);
	
	mem = malloc(72);
	
	fsa = FSAInit(mem, 72, 10);
	
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc - (size_t)fsa), 8);
	
	alloc2 = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc2 - (size_t)fsa), 24);
	
	fsa = FSAInit(mem, 32, 24);
	alloc = FSAAlloc(fsa);
	alloc2 = FSAAlloc(fsa);
	RESULTSTATUS(ENOMEM == errno, 1);
	
	
	free(mem);
}

static void FreeTest(void)
{
	void *mem = NULL;
	fsa_t *fsa = NULL;
	void *alloc = NULL;
	void *alloc2 = NULL;
	
	errno = 0;
	
	mem = malloc(72);
	
	fsa = FSAInit(mem, 32, 24);
	alloc = FSAAlloc(fsa);
	
	FSAFree(fsa, alloc);
	
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(ENOMEM != errno, 1);
	
	fsa = FSAInit(mem, 40, 12);
	
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc - (size_t)fsa), 8);
	
	alloc2 = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc2 - (size_t)fsa), 24);
	
	FSAFree(fsa, alloc);
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(((size_t)alloc - (size_t)fsa), 8);
	
	
	free(mem);
}

static void CountFreeTest(void)
{
	void *mem = NULL;
	fsa_t *fsa = NULL;
	void *alloc = NULL;
	
	errno = 0;
	
	mem = malloc(104);
	
	fsa = FSAInit(mem, 32, 24);
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(FSACountFree(fsa), 0);
	
	FSAFree(fsa, alloc);
	RESULTSTATUS(FSACountFree(fsa), 1);
	
	fsa = FSAInit(mem, 104, 12);
	
	RESULTSTATUS(FSACountFree(fsa), 6);
	
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(FSACountFree(fsa), 5);
	
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(FSACountFree(fsa), 4);
	
	FSAFree(fsa, alloc);
	RESULTSTATUS(FSACountFree(fsa), 5);
	
	alloc = FSAAlloc(fsa);
	alloc = FSAAlloc(fsa);
	alloc = FSAAlloc(fsa);
	alloc = FSAAlloc(fsa);
	RESULTSTATUS(FSACountFree(fsa), 1);
	
	fsa = FSAInit(mem, 100, 8);
	RESULTSTATUS(FSACountFree(fsa), 11);
	
	free(mem);
}

static void SuggestSizeTest(void)
{
	RESULTSTATUS(FSASuggestSize(6, 12), 104);
	
	RESULTSTATUS(FSASuggestSize(0, 0), 8);
	
	RESULTSTATUS(FSASuggestSize(3, 2), 32);
	
	RESULTSTATUS(FSASuggestSize(1000, 1), 8008);
	
	RESULTSTATUS(FSASuggestSize(10,16), 168);
	
	RESULTSTATUS(FSASuggestSize(10,10), 168);
}





