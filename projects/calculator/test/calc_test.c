/*****************************
	Name : Or Beruven

	Reviewed By : Moshe

	Date Test: 07.04.2023

	Description : c file for calculator tests

*****************************/

#include <stdio.h>
#include <assert.h>

#include "calc.h"
#include "utilitiestwo.h"

#define NUM_TESTS 82
#define BUFF_SIZE 64

#define NUM_ERR_TESTS 5
#define ERR_BUFF_SIZE 640

static void CalcTestTomer(void);
static void PrintStatus(calc_status_t status, double result);

static void SimpleExpressionTest(void);
static void ComplexExpressionTest(void);
static void ErrorHandlingTest(void);
static void MentorTest(void);

int main(void)
{
    CalcTestTomer();
    HEADER(Simple Expressions);
    SimpleExpressionTest();
    printf("\n");

    HEADER(More Complex Expressions);
    ComplexExpressionTest();
    printf("\n");

    HEADER(ErrorHandling);
    ErrorHandlingTest();
    printf("\n");

    HEADER(MentorTest);
    MentorTest();
    printf("\n");
    return 0;
}

static void CalcTestTomer(void)
{
    typedef struct calc_test
    {
        char str[BUFF_SIZE];
        double result;
    }calc_test_t;

   typedef struct calc_err_test
    {
        char str[ERR_BUFF_SIZE];
        calc_status_t err_code;
    }calc_err_test_t;

    calc_test_t test_arr[NUM_TESTS] = {
        {"1 + 1", 2},
        {"2 * 3", 6},
        {"7 - 10", -3},
        {"1 / 4", 0.25},
        {"2 ^ 3", 8},
        {"2 + 5 +  3", 10},
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
        {"((5 - 2) * ((3 + 4) / 2)) / (2 + 1)", 3.5}
    };
    
    calc_err_test_t test_err[NUM_ERR_TESTS] = 
    {
        {"1 / 0", DIVISION_BY_ZERO},
        {"100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100", RANGE_EXCEEDED},
        {"1a + 2", SYNTAX_ERROR},
        {"1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1", EXPRESSION_EXCEEDED},
        {"1 + 1)", UNBALANCED_PARENTHESES}
    };

    size_t i = 0;
    calc_status_t status = SUCCESS;
    double result = 0;
    calc_t *calc = CalcCreate(100);

        
    for (i = 0; i < NUM_ERR_TESTS; ++i)
    {
        status = Calculator(calc, test_err[i].str, &result);
        switch (status)
        {
            case SUCCESS:
                printf("Result = %f == %f in line %ld '%s'\n", result, test_arr[i].result, i, test_arr[i].str);
                break;
            
            default:
                if (status != test_err[i].err_code)
                {
                    printf("Result = %f == %f in line %ld '%s'\n", result, test_arr[i].result, i, test_arr[i].str);
 
                }
        }
    }

    for (i = 0; i < NUM_TESTS; ++i)
    {
        status = Calculator(calc, test_arr[i].str, &result);
        switch (status)
        {
            case SUCCESS:
                if (result != test_arr[i].result)
                {
                    printf("Result = %f == %f in line %ld '%s'\n", result, test_arr[i].result, i, test_arr[i].str);
                }

                break;
            
            case SYNTAX_ERROR:
                printf("Syntax_Error line %ld %s\n", i, test_arr[i].str);
                break;
            
            case UNBALANCED_PARENTHESES:
                printf("UNBALANCED_PARENTHESES line %ld\n", i);
                break;
            
            case DIVISION_BY_ZERO:
                printf("DIVISION_BY_ZERO line %ld\n", i);
                break;
            
            case RANGE_EXCEEDED:
                printf("RANGE_EXCEEDED line %ld\n", i);
                break;
            
            case EXPRESSION_EXCEEDED:
                printf("EXPRESSION_EXCEEDED line %ld\n", i);
                break;
        }
    }

    CalcDestroy(calc);
}

static void PrintStatus(calc_status_t status, double result)
{
    switch (status)
    {
        case SUCCESS:
            
            printf("Result = %f\n", result);
            break;
        
        case SYNTAX_ERROR:
            printf("Syntax_Error line\n");
            break;
        
        case UNBALANCED_PARENTHESES:
            printf("UNBALANCED_PARENTHESES\n");
            break;
        
        case DIVISION_BY_ZERO:
            printf("DIVISION_BY_ZERO\n");
            break;
        
        case RANGE_EXCEEDED:
            printf("RANGE_EXCEEDED\n");
            break;
        
        case EXPRESSION_EXCEEDED:
            printf("EXPRESSION_EXCEEDED\n");
            break;
    }
}

static void ErrorHandlingTest(void)
{
    double result = 0;

    /*EXPRESSION_EXCEEDED*/
    calc_t *calc = CalcCreate(2);
    RESULT_STATUS(Calculator(calc, "(2 * 3) + (4 * 5) - (6 / 3)", &result), EXPRESSION_EXCEEDED, EXPRESSION_EXCEEDED);
    RESULT_STATUS(Calculator(calc, "(2 * 3) + 3", &result), SUCCESS,);
    RESULT_STATUS(Calculator(calc, "(2 * 3) + 3 / 2", &result), EXPRESSION_EXCEEDED,);
    CalcDestroy(calc);
    
    /*RANGE_EXCEEDED*/
    calc = CalcCreate(100);
    RESULT_STATUS(Calculator(calc, "1000000000000000000000 ^ 1000999", &result), RANGE_EXCEEDED, RANGE_EXCEEDED);
    RESULT_STATUS(Calculator(calc, "99999 ^ 1000999", &result), RANGE_EXCEEDED, );
    RESULT_STATUS(Calculator(calc, "-99999 ^ 1000999", &result), RANGE_EXCEEDED, );
    RESULT_STATUS(Calculator(calc, "100 ^ 100 ^ 100", &result), RANGE_EXCEEDED, );

    /*DIVISION_BY_ZERO*/
    RESULT_STATUS(Calculator(calc, "2 / 1 / 0", &result), DIVISION_BY_ZERO, DIVISION_BY_ZERO);
    RESULT_STATUS(Calculator(calc, "5 / (2 * 0) / 2", &result), DIVISION_BY_ZERO, );
    RESULT_STATUS(Calculator(calc, "5 / (3 - 3)", &result), DIVISION_BY_ZERO, );

    /*UNBALANCED_PARENTHESES*/
    RESULT_STATUS(Calculator(calc, "5 + (5 - ( 6 + 2)", &result), UNBALANCED_PARENTHESES, UNBALANCED_PARENTHESES);
    RESULT_STATUS(Calculator(calc, "5 + (5 - ( 6 + 2)))", &result), UNBALANCED_PARENTHESES, );    
    RESULT_STATUS(Calculator(calc, "5 + (5 - ( 6 + 2))())", &result), UNBALANCED_PARENTHESES, );    
    RESULT_STATUS(Calculator(calc, "5 + ((5)))", &result), UNBALANCED_PARENTHESES, );  

    /*SYNTAX_ERROR*/
    RESULT_STATUS(Calculator(calc, "5 + (*2)", &result), SYNTAX_ERROR, SYNTAX_ERROR);
    RESULT_STATUS(Calculator(calc, "5 + (+5 + -2)", &result), SUCCESS, );
    RESULT_STATUS(Calculator(calc, "5 * / 2", &result), SYNTAX_ERROR, );
    RESULT_STATUS(Calculator(calc, "5 (* + - *) 2", &result), SYNTAX_ERROR, );
    RESULT_STATUS(Calculator(calc, "/2", &result), SYNTAX_ERROR, );
    RESULT_STATUS(Calculator(calc, "*2", &result), SYNTAX_ERROR, );

    CalcDestroy(calc);
}

static void SimpleExpressionTest(void)
{
    double result = 0;
    calc_t *calc = CalcCreate(100);
    RESULT_STATUS(Calculator(calc, "5 + 2", &result), SUCCESS, Without Unary);
    RESULT_STATUS(result, 7, );

    Calculator(calc, "5 - 2", &result);
    RESULT_STATUS(result, 3, );

    Calculator(calc, "5 - 2 + 2", &result);
    RESULT_STATUS(result, 5, );

    Calculator(calc, "12 - 10 - 22", &result);
    RESULT_STATUS(result, -20, );

    Calculator(calc, "5 - -2", &result);
    RESULT_STATUS(result, 7, With Unary);

    Calculator(calc, "-1 + 10", &result);
    RESULT_STATUS(result, 9, );
    
    Calculator(calc, "-(-(2 + 2))", &result);
    RESULT_STATUS(result, 4, );
    CalcDestroy(calc);
}

static void ComplexExpressionTest(void)
{
    double result = 0;
    calc_t *calc = CalcCreate(100);
    RESULT_STATUS(Calculator(calc, "5 * 2", &result), SUCCESS, *);
    RESULT_STATUS(result, 10, );

    Calculator(calc, "6 * 2 * 3 * 1", &result);
    RESULT_STATUS(result, 36, );

    Calculator(calc, "22 * 4 * 1 * 1", &result);
    RESULT_STATUS(result, 88, );

    Calculator(calc, "6 / 2", &result);
    RESULT_STATUS(result, 3, /);

    Calculator(calc, "20 / 2 / 5", &result);
    RESULT_STATUS(result, 2, );

    Calculator(calc, "5 / 2 * 2", &result);
    RESULT_STATUS(result, 5, */);

    Calculator(calc, "10 / 5 * 2 / 2 * 10", &result);
    RESULT_STATUS(result, 20, );

    Calculator(calc, "12 - (10 - 22)", &result);
    RESULT_STATUS(result, 24, ());

    Calculator(calc, "5 * (10 / 2)", &result);
    RESULT_STATUS(result, 25, );

    Calculator(calc, "2 - 2 ^ 2 * 2 - 2", &result);
    RESULT_STATUS(result, -8, ^);

    Calculator(calc, "(1 + 1) ^ (0 + 2) ^ 3", &result);
    RESULT_STATUS(result, 256, );

    CalcDestroy(calc);
}

static void MentorTest()
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

    assert(SUCCESS == Calculator(calc, str,&res));
    assert(15 == res);

    assert(SUCCESS == Calculator(calc, str2,&res));
    assert(0 == res);

    assert(SYNTAX_ERROR == Calculator(calc, str3,&res));
    assert(0 == res);

    assert(DIVISION_BY_ZERO == Calculator(calc, str4,&res));
    assert(0 == res);
    
    assert(SUCCESS == Calculator(calc, str5,&res));
    assert(48 == res);
    
    assert(UNBALANCED_PARENTHESES  == Calculator(calc, str6,&res));
    assert(0 == res);

    assert(UNBALANCED_PARENTHESES  == Calculator(calc, str7,&res));
    assert(0 == res);

    RESULT_STATUS(1, 1,Mentor Status);
    CalcDestroy(calc);
    
}