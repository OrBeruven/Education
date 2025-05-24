/****************************
*   Sched.c for Calculator  *
*   Developer : Moshe       *
*   reviewer : Neviu        *
*   Date : 10 .04 .23       *
****************************/
#include <stdio.h> /*printf*/
#include <assert.h>
#include "calc.h"

#define PRINT_UNDERLINE(str) printf("\n\033[4m%s\033[0m\n", str);

#define PRINT_TEST(x)                       \
	if (x)                                  \
	{                                       \
		printf("\033[32mSUCCESS\033[0m\n"); \
	}                                       \
	else                                    \
	{                                       \
		printf("\033[31mFAILURE\033[0m\n"); \
	}

typedef struct test
{
	char str[50];
	double result;
} test_t;

typedef struct test_error
{
	char str[50];
	double result;
	calc_status_t status;
} test_error_t;

/************************************/

void PrintStatus(calc_status_t status);
void Test1();
void TestError();
void Test0();
void MentorTest();

/************************************/

void KingTest()
{
	calc_status_t status = 0;
	calc_t *new_c = NULL;
	double res = 0;
	size_t i = 0;

	test_error_t test_arr[] =
		{
			{"1 +++ 1", 0, SYNTAX_ERROR},
			{"1++ 1", 0, SYNTAX_ERROR},
			{"-(-(1+1))", 2, SUCCESS}};

	size_t length = sizeof(test_arr) / sizeof(test_arr[0]);

	new_c = CalcCreate(100);

	for (i = 0; i < length; ++i)
	{

		printf("\n\033[4mTest Error number %lu\033[0m\n", i + 1);
		printf("passed argument = %s \nexpected result = %.2f\n", test_arr[i].str, test_arr[i].result);
		status = Calculator(new_c, test_arr[i].str, &res);
		printf("returned result = %.2f\n", res);

		PRINT_TEST(res == test_arr[i].result);

		printf("returned status = ");
		PrintStatus(status);
		PRINT_TEST(status == test_arr[i].status);
	}
	CalcDestroy(new_c);
}

void TestKing()
{
	calc_status_t status = 0;
	calc_t *new_c = NULL;
	double res = 0;
	size_t i = 0;

	test_t test_arr[] =
		{

			{"8++8*3+-2^5", 0}};

	size_t length = sizeof(test_arr) / sizeof(test_arr[0]);

	new_c = CalcCreate(100);

	for (i = 0; i < length; ++i)
	{
		printf("\n\033[4mTest number %lu\033[0m\n", i + 1);
		printf("passed argument = %s \nexpected result = %.2f\n", test_arr[i].str, test_arr[i].result);
		status = Calculator(new_c, test_arr[i].str, &res);
		printf("returned result = %.2f\n", res);
		printf("returned status = ");
		PrintStatus(status);
		PRINT_TEST(res == test_arr[i].result);
	}

	CalcDestroy(new_c);
}

int main()
{
	KingTest();

	Test0();
	Test1();
	TestError();
	MentorTest();

	printf("Finished ALL TESTS\n");

	return 0;
}

void MentorTest()
{
	double res = 0;
	calc_t *calc = NULL;
	char str[100] = "8 + 7";
	char str2[100] = "8++8*3+-2^5";
	char str3[100] = "8+8*3-2^";
	char str4[100] = "2/0";
	char str5[100] = "8++8*((3-2)*5)";
	char str6[100] = "3-2)*5";
	char str7[100] = "(3-2)*5+ 5*(4+4+4";

	calc = CalcCreate(30);

	assert(SUCCESS == Calculator(calc, str, &res));
	assert(15 == res);

	assert(SUCCESS == Calculator(calc, str2, &res));
	assert(0 == res);

	assert(SYNTAX_ERROR == Calculator(calc, str3, &res));
	assert(0 == res);

	assert(DIVISION_BY_ZERO == Calculator(calc, str4, &res));
	assert(0 == res);

	assert(SUCCESS == Calculator(calc, str5, &res));
	assert(48 == res);

	assert(UNBALANCED_PARENTHESES == Calculator(calc, str6, &res));
	assert(0 == res);

	assert(UNBALANCED_PARENTHESES == Calculator(calc, str7, &res));
	assert(0 == res);

	printf("mentor test - SUCCESS\n");
	CalcDestroy(calc);
}

void Test0()
{
	calc_status_t status = 0;
	calc_t *new_c = NULL;
	double res = 0;
	size_t i = 0;

	test_error_t test_arr[] =
		{
			{"(2 * 3) + (4 * 5) - (6 / 3)", 0, EXPRESSION_EXCEEDED},
			{"(2 * 3) + 3", 9, SUCCESS},
			{"(2 * 3) + 3 / 2", 0, EXPRESSION_EXCEEDED}};

	size_t length = sizeof(test_arr) / sizeof(test_arr[0]);

	new_c = CalcCreate(2);

	for (i = 0; i < length; ++i)
	{

		printf("\n\033[4mTest Error number %lu\033[0m\n", i + 1);
		printf("passed argument = %s \nexpected result = %.2f\n", test_arr[i].str, test_arr[i].result);
		status = Calculator(new_c, test_arr[i].str, &res);
		printf("returned result = %.2f\n", res);

		PRINT_TEST(res == test_arr[i].result);

		printf("returned status = ");
		PrintStatus(status);
		PRINT_TEST(status == test_arr[i].status);
	}
	CalcDestroy(new_c);
}

void Test1()
{
	calc_status_t status = 0;
	calc_t *new_c = NULL;
	double res = 0;
	size_t i = 0;

	test_t test_arr[] =
		{
			{"8++8*((3-2)*5)", 48},
			{"1 ++ 1", 0},
			{"1 / 4", 0.25},
			{"2 ^ 3", 8},
			{"(-2) *-(2^4)", 32},
			{"2 * 3 * 4", 24},
			{"-1 + 10", 9},
			{"+4 + 3", 7},
			{"1 + 3 - 7", -3},
			{"2 * 3 + 1", 7},
			{"1 + 2 * 3", 7},
			{"-1 + 8", 7},
			{"-1 - -8", 7},
			{"+9 - -8", 17},
			{"2 * (3 + 4)", 14},
			{"(3 + 4)*  2", 14},
			{"1 / 2 + 2", 2.5},
			{"2 + 1 / 2", 2.5},
			{"3*(2+1)", 9},
			{"10 - -5", 15},
			{"-5 + 10 + 15", 20},
			{"3 ^ 2", 9},
			{"9 / 3", 3},
			{"(5 + 3) * 2", 16},
			{"2 + 3 * 4", 14},
			{"(2 + 3) * 4", 20},
			{"2 ^ 0", 1},
			{"(2 + 3) ^ 2", 25},
			{"1 + 2 * 3 + 4 * 5 + 6", 33},
			{"(1 + 2) * (3 + 4)", 21},
			{"(1 + 2) * 3 + 4", 13},
			{"1 * 2 + 3 * 4", 14},
			{"3 ^ 2 + 4 ^ 2", 25},
			{"2 ^ 2 + 3 ^ 2 + 4 ^ 2", 29},
			{"(1 + 2) * 3", 9},
			{"(2 * 3) + 4", 10},
			{"(5 - 2) * (4 + 1)", 15},
			{"(10 - 5) / 5", 1},
			{"(3 + 5) / (2 * 2)", 2},
			{"(2 * 3) ^ 2", 36},
			{"(3 + 4) ^ 2", 49},
			{"(4 - 2) ^ 3", 8},
			{"2 * (3 + 4)", 14},
			{"4 / (2 + 2)", 1},
			{"(2 ^ 3) / 4", 2},
			{"3 * (4 + 5) / 2", 13.5},
			{"(3 + 4 * 5) / (2 - 3)", -23},
			{"(2 * 3 + 4) * 5", 50},
			{"(2 + 3) * (4 + 5)", 45},
			{"(1 + 2 + 3 + 4) * 5", 50},
			{"5 * (1 + 2 + 3 + 4)", 50},
			{"(2 + 3) * 4 - 5", 15},
			{"2 + (3 * 4 - 5)", 9},
			{"(1 + 2) ^ (3 - 1)", 9},
			{"2 ^ (1 + 3)", 16},
			{"(3 - 1) ^ (1 + 2)", 8},
			{"2 + 3 * 4 ^ 2", 50},
			{"(2 + 3) * 4 ^ 2", 80},
			{"(2 ^ 3) * (4 / 2)", 16},
			{"2 ^ (3 * 4) / 4", 1024},
			{"(2 * 3) + (4 * 5) - (6 / 3)", 24},
			{"(1 + 2) * (3 + 4) * (5 + 6)", 231},
			{"(1 + 1) ^ (0 + 2) ^ 3", 256},
			{"2 + (3 * 4) ^ 2 + 5", 151},
			{"(2 + 3 * 4) ^ 2 + 5", 201},
			{"(2 ^ 3) * (4 / 2) + 5", 21},
			{"2 ^ (3 * 4) / 4 - 5", 1019},
			{"(2 * 3) + (4 * 5) - (6 / 3) ^ 2", 22},
			{"(1 + 2) * (3 + 4) * (5 + 6) / 7", 33},
			{"3 ^ 2 ^ 2 * 3", 243},
			{"(((1 + 1)))", 2},
			{"  (  (((( 2 + 2 ) * 2)  ) ))", 8},
			{"-(1 + 2)", -3},
			{"+(1 + 2)", 3},
			{"((+3 - -2) * 4 - 2) / (5 - 1)", 4.5},
			{"(2 + (3 * 4)) / ((-5 + +9) * 2)", 1.75},
			{"((2 + 3) * (4 - 1)) / (5 - (2 + 1))", 7.5},
			{"((10 / 2) - 3) * ((+6 - 2)^2)", 32},
			{"((2 * 3) + 4) / ((5 - 1) * (2 - 1))", 2.5},
			{"((10 - (3 * 2)) / 4) + (6 - 2)^2", 17},
			{"((5 - 2) * ((3 + 4) / 2)) / (2 + 1)", 3.5},
			{"8 + 7", 15},
			{"8++8*3+-2^5", 0}};

	size_t length = sizeof(test_arr) / sizeof(test_arr[0]);

	new_c = CalcCreate(100);

	for (i = 0; i < length; ++i)
	{
		printf("\n\033[4mTest number %lu\033[0m\n", i + 1);
		printf("passed argument = %s \nexpected result = %.2f\n", test_arr[i].str, test_arr[i].result);
		status = Calculator(new_c, test_arr[i].str, &res);
		printf("returned result = %.2f\n", res);
		printf("returned status = ");
		PrintStatus(status);
		PRINT_TEST(res == test_arr[i].result);
	}

	CalcDestroy(new_c);
}

void TestError()
{
	calc_status_t status = 0;
	calc_t *new_c = NULL;
	double res = 0;
	size_t i = 0;

	test_error_t test_arr[] =
		{

			{"8+8*3-2^", 0, SYNTAX_ERROR},
			{"3-2)*5", 0, UNBALANCED_PARENTHESES},
			{"(3-2)*5+ 5*(4+4+4", 0, UNBALANCED_PARENTHESES},
			{"2/0", 0, DIVISION_BY_ZERO},
			{"100^100^100", 0, RANGE_EXCEEDED},
		};

	size_t length = sizeof(test_arr) / sizeof(test_arr[0]);

	new_c = CalcCreate(100);

	for (i = 0; i < length; ++i)
	{
		if (i == 34)
		{
			printf("str = %s\n", test_arr[i].str);
		}
		printf("\n\033[4mTest Error number %lu\033[0m\n", i + 1);
		printf("passed argument = %s \nexpected result = %.2f\n", test_arr[i].str, test_arr[i].result);
		status = Calculator(new_c, test_arr[i].str, &res);
		printf("returned result = %.2f\n", res);

		PRINT_TEST(res == test_arr[i].result);

		printf("returned status = ");
		PrintStatus(status);
		PRINT_TEST(status == test_arr[i].status);
	}

	CalcDestroy(new_c);
}

void PrintStatus(calc_status_t status)
{
	switch (status)
	{
	case 0:
	{
		printf("SUCCESS\n");
		break;
	}

	case 1:
	{
		printf("SYNTAX_ERROR\n");
		break;
	}
	case 2:
	{
		printf("UNBALANCED_PARENTHESES\n");
		break;
	}
	case 3:
	{
		printf("DIVISION_BY_ZERO\n");
		break;
	}
	case 4:
	{
		printf("RANGE_EXCEEDED\n");
		break;
	}
	case 5:
	{
		printf("EXPRESSION_EXCEEDED\n");
		break;
	}
	}
}
