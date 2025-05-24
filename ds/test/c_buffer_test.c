/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for c_buffer tests

*****************************/

#include <stdio.h> /*using - printf*/

#include "../include/c_buffer.h"

/*******************************************************************************
Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void WriteTest(void);

static void ReadTest(void);

static void FreeSpaceTest(void);

static void SizeTest(void);

static void IsEmptyTest(void);

static void ResultStatus(int status, int expected_status);

#define GREEN_OUT_PUT printf("\033[0;32m");

#define RED_OUT_PUT printf("\033[0;31m");

#define NORMAL_OUT_PUT printf("\033[0m");

/*******************************************************************************
*******************************************************************************/


int main()
{
	printf("Testing Create and Destroy : \n");
	CreateDestroyTest();
	printf("\n");	
	
	
	printf("Testing Write :\n");
	WriteTest();
	printf("\n");	
	
	
	printf("Testing Read :\n");
	ReadTest();
	printf("\n");
	
	
	printf("Testing Free Space :\n");	
	FreeSpaceTest();
	printf("\n");	
	
	
	printf("Testing Size :\n");
	SizeTest();
	printf("\n");
	
	
	printf("Testing IsEmpty :\n");
	IsEmptyTest();
	printf("\n");
	/*
	printf("Testing Peek :\n");
	PeekTest();
	printf("\n");
	
	
	
	
	
	printf("Testing Append :\n");
	AppendTest();*/
	printf("\n");
	return 0;
}


/**************************************************************************************
			Test Functions
**************************************************************************************/


static void ResultStatus(int status, int expected_status)
{
	if (status == expected_status)
	{
		GREEN_OUT_PUT
		printf("Success\n");
		NORMAL_OUT_PUT
	}
	else
	{
		RED_OUT_PUT
		printf("Failure\n");
		NORMAL_OUT_PUT
	}
}


static void CreateDestroyTest(void)
{
	c_buffer_t *buff1 = NULL;
	c_buffer_t *buff2 = NULL;
	

	buff1 = CBufferCreate(1);
	ResultStatus(buff1 == NULL, 0);
	
	CBufferDestroy(buff1);
	
	buff1 = CBufferCreate(12);
	ResultStatus(buff1 == NULL, 0);
	
	buff2 = CBufferCreate(2);
	ResultStatus(buff2 == NULL, 0);
	
	CBufferDestroy(buff1);
	CBufferDestroy(buff2);
}

static void WriteTest(void)
{
	c_buffer_t *buff1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int temp = 0;
	
	buff1 = CBufferCreate(12);
	
	ResultStatus(CBufferWrite(buff1, (void *)&num1, 4), 4);
	ResultStatus(CBufferWrite(buff1, (void *)&num2, 4), 4);
	ResultStatus(CBufferWrite(buff1, (void *)&num3, 4), 4);
	ResultStatus(CBufferWrite(buff1, (void *)&num4, 4), -1);
	
	CBufferRead(buff1, (void *)&temp,  4);
	CBufferRead(buff1, (void *)&temp,  4);
	
	ResultStatus(CBufferWrite(buff1, (void *)&num4, 4), 4);
	ResultStatus(CBufferWrite(buff1, (void *)&num1, 4), 4);
	
	CBufferDestroy(buff1);
}

static void ReadTest(void)
{
	c_buffer_t *buff1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int result = 0;
	
	buff1 = CBufferCreate(12);
	
	CBufferWrite(buff1, (void *)&num1, 4);
	ResultStatus(CBufferRead(buff1, (void *)&result,  4), 4);
	ResultStatus(CBufferIsEmpty(buff1), 1);
	ResultStatus(result, 1);
	

	CBufferWrite(buff1, (void *)&num1, 4);
	CBufferWrite(buff1, (void *)&num2, 4);
	ResultStatus(CBufferRead(buff1, (void *)&result,  4), 4);
	ResultStatus(result, 1);
	ResultStatus(CBufferRead(buff1, (void *)&result,  4), 4);
	ResultStatus(result, 2);
	
	CBufferWrite(buff1, (void *)&num3, 4);
	CBufferWrite(buff1, (void *)&num4, 4);
	CBufferWrite(buff1, (void *)&num1, 4);
	CBufferWrite(buff1, (void *)&num2, 4);
	
	ResultStatus(CBufferRead(buff1, (void *)&result,  4), 4);

	ResultStatus(result, 3);
	
	CBufferDestroy(buff1);
}


static void FreeSpaceTest(void)
{
	c_buffer_t *buff1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int result = 0;
	
	buff1 = CBufferCreate(12);
	
	CBufferWrite(buff1, (void *)&num1, 4);
	ResultStatus(CBufferFreeSpace(buff1), 8);

	
	CBufferWrite(buff1, (void *)&num2, 4);
	ResultStatus(CBufferFreeSpace(buff1), 4);
	
	CBufferWrite(buff1, (void *)&num3, 4);
	ResultStatus(CBufferFreeSpace(buff1), 0);
	
	CBufferWrite(buff1, (void *)&num4, 4);
	ResultStatus(CBufferFreeSpace(buff1), 0);
	
	CBufferRead(buff1, (void *)&result,  4);
	ResultStatus(CBufferFreeSpace(buff1), 4);

	CBufferDestroy(buff1);
}


static void SizeTest(void)
{
	c_buffer_t *buff1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int result = 0;
	
	buff1 = CBufferCreate(12);
	
	CBufferWrite(buff1, (void *)&num1, 4);
	ResultStatus(CBufferSize(buff1), 4);

	
	CBufferWrite(buff1, (void *)&num2, 4);
	ResultStatus(CBufferSize(buff1), 8);
	
	CBufferWrite(buff1, (void *)&num3, 4);
	ResultStatus(CBufferSize(buff1), 12);
	
	CBufferWrite(buff1, (void *)&num4, 4);
	ResultStatus(CBufferSize(buff1), 12);
	
	CBufferRead(buff1, (void *)&result,  4);
	ResultStatus(CBufferSize(buff1), 8);
	
	CBufferWrite(buff1, (void *)&num4, 4);
	CBufferRead(buff1, (void *)&result,  4);
	CBufferRead(buff1, (void *)&result,  4);
	ResultStatus(CBufferSize(buff1), 4);
	
	CBufferDestroy(buff1);
}


static void IsEmptyTest(void)
{
	c_buffer_t *buff1 = NULL;
	
	int num1 = 1;
	int num2 = 2;
	int result = 0;
	
	buff1 = CBufferCreate(12);
	ResultStatus(CBufferIsEmpty(buff1), 1);
	
	CBufferWrite(buff1, (void *)&num1, 4);
	ResultStatus(CBufferIsEmpty(buff1), 0);

	
	CBufferWrite(buff1, (void *)&num2, 4);
	ResultStatus(CBufferIsEmpty(buff1), 0);
	
	CBufferRead(buff1, (void *)&result,  4);
	ResultStatus(CBufferIsEmpty(buff1), 0);
	
	CBufferRead(buff1, (void *)&result,  4);
	ResultStatus(CBufferIsEmpty(buff1), 1);
	
	CBufferDestroy(buff1);
}















