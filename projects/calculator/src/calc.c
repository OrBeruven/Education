/*****************************
	Name : Or Beruven

	Reviewed By : Moshe

	Date Test: 07.04.2023

	Description : c file for calculator implementation

*****************************/

#include <stdlib.h> /*free, malloc, strtod*/
#include <stdio.h>  /*perror*/
#include <math.h>   /*pow*/
#include <errno.h>  /*errno, ENOMEM*/
#include <assert.h> /*assert*/

#include "../include/calc.h"
#include "../include/stack.h"

#define ASCII 256
#define IS_EXCEEDED(x) ((x) == HUGE_VAL || (x) == -HUGE_VAL)

typedef enum stack_type
{
    OPERAND = 0,
    OPERATOR = 1,
    NUM_OF_STACKS = 2
} stack_type_t;

typedef enum states
{
    BAD = 0,
    INIT = 1,
    VALID = 2,
    EXPECTING_NUM = 3,
    NUM_OF_STATES
}states_t;

typedef states_t (*action_t)(calc_t *calc, char **expression, double *result);
typedef calc_status_t (*calc_func_t)(double lhs, double rhs, double *result);
typedef states_t (*minus_handler_t)(calc_t *calc, char **expression, double *result);

typedef enum char_types
{
    NUM = 0,
    OPER = 1,
    INVALID = 2,
    MINUS = 3,
    PLUS = 4,
    OPEN_PARANTH = 5,
    CLOSED_PARANTH = 6,
    SPACE = 7,
    DIVMUL = 8,
    NUM_OF_INPUTS
}char_types_t;

struct calculator
{
	stack_t *stack[NUM_OF_STACKS];

	action_t action_lut[NUM_OF_STATES][NUM_OF_INPUTS];
    calc_status_t status;
    double result;
    states_t state;
};

static void InitLut(action_t lut[NUM_OF_STATES][NUM_OF_INPUTS]);
static void CleanCalc(calc_t *calc);
static int CheckOperandExceeded(calc_t *calc);
static int CheckOperatorExceeded(calc_t *calc);

/*All Action Functions*/
static states_t Error(calc_t *calc, char **expression, double *result);
static states_t Space(calc_t *calc, char **expression, double *result);
static states_t PushNum(calc_t *calc, char **expression, double *result);
static states_t PushOp(calc_t *calc, char **expression, double *result);
static states_t PushDivMul(calc_t *calc, char **expression, double *result);
static states_t PushUnary(calc_t *calc, char **expression, double *result);
static states_t PushOpenParenth(calc_t *calc, char **expression, double *result);
static states_t PushClosedParenth(calc_t *calc, char **expression, double *result);
static states_t PushMinus(calc_t *calc, char **expression, double *result);

/*Minus function handlers*/
static states_t MinusHandlerForMinus(calc_t *calc, char **expression, double *result);
static states_t MinusHandlerForOpenParen(calc_t *calc, char **expression, double *result);
static states_t MinusHandlerForElse(calc_t *calc, char **expression, double *result);
/*****************************************************************************************/


static void CalculateTwoNum(calc_t *calc, double *result);

/***********LUT***********/
static int char_type[ASCII] =  {INVALID};
static int precedence_table[ASCII] =  {0};
static calc_func_t calc_lut[ASCII] =  {NULL};
minus_handler_t minus_lut[NUM_OF_INPUTS] = {MinusHandlerForMinus, MinusHandlerForElse, MinusHandlerForElse, MinusHandlerForElse, 
                                            MinusHandlerForElse, MinusHandlerForOpenParen, MinusHandlerForElse, MinusHandlerForElse};


/*Caulculate Functions*/
static calc_status_t SyntaxError(double lhs, double rhs, double *result);
static calc_status_t Add(double lhs, double rhs, double *result);
static calc_status_t Sub(double lhs, double rhs, double *result);
static calc_status_t Mul(double lhs, double rhs, double *result);
static calc_status_t Div(double lhs, double rhs, double *result);
static calc_status_t Pow(double lhs, double rhs, double *result);
static calc_status_t OpenParan(double lhs, double rhs, double *result);


/*********************API functions*************************/
calc_t *CalcCreate(size_t max_exp)
{
    size_t i = 0;
    size_t j = 0;
    calc_t *new_calc = NULL;

    assert(0 != max_exp);

    new_calc = (calc_t *)malloc(sizeof(calc_t));
    if (NULL == new_calc)
    {
        errno = ENOMEM;
        perror("CalcCreate");
        return NULL;
    }

    for (i = 0; i < NUM_OF_STACKS; ++i)
    {
        new_calc->stack[i] = StackCreate(max_exp, sizeof(double));
        if (NULL == new_calc->stack[i])
        {
            for (j = 0; j < i; ++j)
            {
                free(new_calc->stack[j]);
            }
            free(new_calc);
            errno = ENOMEM;
            return NULL;
        }
    }

    new_calc->state = INIT;
    new_calc->status = SUCCESS;
    InitLut((new_calc->action_lut));
    return new_calc;
}

calc_status_t Calculator(calc_t *calc, const char *expression, double *result)
{
    char **expression_p = NULL;
    char ch = 0;

    assert(NULL != calc);
    assert(NULL != expression);
    assert(NULL != result);

    expression_p = (char **)&expression;
    ch = *(char *)expression;

    CleanCalc(calc);

    while (BAD != calc->state && '\0' != ch && SUCCESS == calc->status)
    {
        calc->state = calc->action_lut[calc->state][char_type[(int)ch]](calc, expression_p, result);
        ch = *(char *)expression;
    }

    while (!StackIsEmpty(calc->stack[OPERATOR]) && SUCCESS == calc->status && VALID == calc->state)
    {
        CalculateTwoNum(calc, result);
    }

    if (VALID != calc->state && EXPRESSION_EXCEEDED != calc->status && UNBALANCED_PARENTHESES != calc->status && DIVISION_BY_ZERO != calc->status)
    {
        *result = 0;
        calc->status = SYNTAX_ERROR;
    }

    return calc->status;
}

void CalcDestroy(calc_t *calc)
{
    size_t i = 0;

    assert(NULL != calc);

    for (i = 0; i < NUM_OF_STACKS; ++i)
    {
        StackDestroy(calc->stack[i]);
    }

    free(calc);
}

/******************************************************************/

static void InitLut(action_t lut[NUM_OF_STATES][NUM_OF_INPUTS])
{
    size_t i = 0;

    /*Char Type Init*/
    for (i = 0; i < ASCII; ++i)
    {
        char_type[i] = INVALID;
    }

    for (i = '0'; i <= '9'; ++i)
    {
        char_type[i] = NUM;
    }

    char_type[' '] = SPACE;
    char_type['+'] = PLUS;
    char_type['-'] = MINUS;
    char_type['*'] = DIVMUL;
    char_type['/'] = DIVMUL;
    char_type['^'] = OPER;
    char_type['('] = OPEN_PARANTH;
    char_type[')'] = CLOSED_PARANTH;

    /*Precedence Table Init*/
    for (i = 0; i < ASCII; ++i)
    {
        precedence_table[i] = 0;
    }

    precedence_table['+'] = 1;
    precedence_table['-'] = 2;
    precedence_table['*'] = 3;
    precedence_table['/'] = 3;
    precedence_table['^'] = 4;
    precedence_table['('] = 1;
    precedence_table[')'] = 5;

    /*Calc Lut Init*/
    for (i = 0; i < ASCII; ++i)
    {
        calc_lut[i] = SyntaxError;
    }
    calc_lut['+'] = Add;
    calc_lut['-'] = Sub;
    calc_lut['*'] = Mul;
    calc_lut['/'] = Div;
    calc_lut['^'] = Pow;
    calc_lut['('] = OpenParan;

    /*Calc State Init*/
    lut[INIT][NUM] = PushNum;
    lut[INIT][OPER] = Error;
    lut[INIT][PLUS] = PushNum;
    lut[INIT][MINUS] = PushMinus;
    lut[INIT][OPEN_PARANTH] = PushOpenParenth;
    lut[INIT][CLOSED_PARANTH] = Error;
    lut[INIT][SPACE] = Space;
    lut[INIT][DIVMUL] = Error;
    lut[INIT][INVALID] = Error;

    lut[VALID][NUM] = Error;
    lut[VALID][OPER] = PushOp;
    lut[VALID][PLUS] = PushOp;
    lut[VALID][MINUS] = PushMinus;
    lut[VALID][OPEN_PARANTH] = PushOpenParenth;
    lut[VALID][CLOSED_PARANTH] = PushClosedParenth;
    lut[VALID][SPACE] = Space;
    lut[VALID][DIVMUL] = PushDivMul;
    lut[VALID][INVALID] = Error;

    lut[EXPECTING_NUM][NUM] = PushNum;
    lut[EXPECTING_NUM][OPER] = Error;
    lut[EXPECTING_NUM][PLUS] = PushUnary;
    lut[EXPECTING_NUM][MINUS] = PushUnary;
    lut[EXPECTING_NUM][OPEN_PARANTH] = PushOpenParenth;
    lut[EXPECTING_NUM][CLOSED_PARANTH] = PushClosedParenth;
    lut[EXPECTING_NUM][SPACE] = Space;
    lut[EXPECTING_NUM][DIVMUL] = Error;
    lut[EXPECTING_NUM][INVALID] = Error;

    lut[BAD][NUM] = Error;
    lut[BAD][OPER] = Error;
    lut[BAD][PLUS] = Error;
    lut[BAD][MINUS] = Error;
    lut[BAD][OPEN_PARANTH] = Error;
    lut[BAD][CLOSED_PARANTH] = Error;
    lut[BAD][SPACE] = Error;
    lut[BAD][DIVMUL] = Error;
    lut[BAD][INVALID] = Error;
}

static void CleanCalc(calc_t *calc)
{
    size_t i = 0;

    calc->result = 0;
    calc->state = INIT;
    calc->status = SUCCESS;

    for (i = 0; i < NUM_OF_STACKS; ++i)
    {
        while (!StackIsEmpty(calc->stack[i]))
        {
            StackPop(calc->stack[i]);
        }
    }
}

static int CheckOperandExceeded(calc_t *calc)
{
   
    if (StackSize(calc->stack[OPERAND]) == StackCapacity(calc->stack[OPERAND]))
    {
        calc->status = EXPRESSION_EXCEEDED;
        calc->state = BAD;
        return 1;
    }

    return 0;
}

static int CheckOperatorExceeded(calc_t *calc)
{
   
    if (StackSize(calc->stack[OPERATOR]) == StackCapacity(calc->stack[OPERATOR]))
    {
        calc->status = EXPRESSION_EXCEEDED;
        calc->state = BAD;
        return 1;
    }

    return 0;
}

/*****************Char Type Handlers******************/
static states_t Error(calc_t *calc, char **expression, double *result)
{
	calc->status = SYNTAX_ERROR;

    (void)expression;
    (void)result;

	return BAD;
}	

static states_t Space(calc_t *calc, char **expression, double *result)
{
	++(*expression);

    (void)result;

    return calc->state;
}	

static states_t PushNum(calc_t *calc, char **expression, double *result)
{
	double num = 0;
	errno = 0;
	num = strtod(*expression, expression);
	
	if (0 != errno)
	{
		calc->status = SYNTAX_ERROR;
		*result = 0;
		
		return BAD;
	}

    if (CheckOperandExceeded(calc))
    {
        *result = 0;
        return BAD;
    }

    StackPush(calc->stack[OPERAND], (const void *)&num);
    calc->status = SUCCESS;
    return VALID;
}

static states_t PushOp(calc_t *calc, char **expression, double *result)
{
	char operator = **expression;

    while (!StackIsEmpty(calc->stack[OPERATOR]) && precedence_table[(int)operator] < precedence_table[(int)*(char *)StackPeek(calc->stack[OPERATOR])])
    {
        CalculateTwoNum(calc, result);
    }

	StackPush(calc->stack[OPERATOR], (const void*)&operator);
	++(*expression);
	calc->status = SUCCESS;

	return EXPECTING_NUM;
}

static states_t PushDivMul(calc_t *calc, char **expression, double *result)
{
	char operator = **expression;

    while (!StackIsEmpty(calc->stack[OPERATOR]) && precedence_table[(int)operator] <= precedence_table[(int)*(char *)StackPeek(calc->stack[OPERATOR])])
    {
        CalculateTwoNum(calc, result);
    }

    if (CheckOperatorExceeded(calc))
    {
        *result = 0;
        return BAD;
    }
	StackPush(calc->stack[OPERATOR], (const void*)&operator);
	++(*expression);
	return EXPECTING_NUM;
}

static states_t PushUnary(calc_t *calc, char **expression, double *result)
{
    double num = 0;

    if ('(' == *(*expression + 1))
    {
        return MinusHandlerForOpenParen(calc, expression, result);
    }

    if (' ' == *(*expression + 1))
    {
        calc->state = BAD;
        calc->status = SYNTAX_ERROR;
        return BAD;
    }

    num = strtod(*expression, expression);
    
	StackPush(calc->stack[OPERAND], (const void*)&num);
	calc->status = SUCCESS;

    (void)result;

	return VALID;
}

static states_t PushMinus(calc_t *calc, char **expression, double *result)
{   
    return minus_lut[char_type[(int)*(*expression + 1)]](calc, expression, result);
}

static states_t PushClosedParenth(calc_t *calc, char **expression, double *result)
{
    while (!StackIsEmpty(calc->stack[OPERATOR]) && '(' != *(char *)StackPeek(calc->stack[OPERATOR]))
    {
        CalculateTwoNum(calc, result);
    }

    if (StackIsEmpty(calc->stack[OPERATOR]))
    {
        *result = 0;
        calc->status = UNBALANCED_PARENTHESES;
        return BAD;
    }
    
    StackPop(calc->stack[OPERATOR]);
    
	++(*expression);
	calc->status = SUCCESS;
	
	return VALID;
}

static states_t PushOpenParenth(calc_t *calc, char **expression, double *result)
{
	char operator = **expression;

	StackPush(calc->stack[OPERATOR], (const void*)&operator);

    (void)result;

	++(*expression);
	calc->status = SUCCESS;

	return EXPECTING_NUM;
}


/******************Minus Handler Functions************************/
static states_t MinusHandlerForMinus(calc_t *calc, char **expression, double *result)
{
    char operator = '+';
    double num = 0;
    ++(*expression);
    num = strtod(*expression, expression);
    num *= -1;

    while (!StackIsEmpty(calc->stack[OPERATOR]) && precedence_table[(int)operator] < precedence_table[(int)*(char *)StackPeek(calc->stack[OPERATOR])])
    {
        CalculateTwoNum(calc, result);
    }

    if (calc->state == VALID)
    {
        StackPush(calc->stack[OPERATOR], (const void*)&operator);
    }
    StackPush(calc->stack[OPERAND], (const void *)&num);
    return VALID;
}

static states_t MinusHandlerForOpenParen(calc_t *calc, char **expression, double *result)
{
    char operator = '*';
    double num = -1;

    (void)result;
    ++(*expression);

    StackPush(calc->stack[OPERAND], (const void *)&num);
    StackPush(calc->stack[OPERATOR], (const void*)&operator);

    return EXPECTING_NUM;
}

static states_t MinusHandlerForElse(calc_t *calc, char **expression, double *result)
{
    char operator = **expression;

    while (!StackIsEmpty(calc->stack[OPERATOR]) && precedence_table[(int)operator] <= precedence_table[(int)*(char *)StackPeek(calc->stack[OPERATOR])])
    {
        CalculateTwoNum(calc, result);
    }

    StackPush(calc->stack[OPERATOR], (const void*)&operator);
    ++(*expression);
    calc->status = SUCCESS;

    return EXPECTING_NUM;
}
/*******************************************************************************/

static void CalculateTwoNum(calc_t *calc, double *result)
{
	double lhs = 0;
	double rhs = 0;
	char operator = 0;
	
	rhs = *(double *)StackPeek(calc->stack[OPERAND]);
	StackPop(calc->stack[OPERAND]);

	lhs = *(double *)StackPeek(calc->stack[OPERAND]);
	StackPop(calc->stack[OPERAND]);

	operator = *(char *)StackPeek(calc->stack[OPERATOR]);
	StackPop(calc->stack[OPERATOR]);
	
    calc->status = calc_lut[(int)operator](lhs, rhs, result);

    if (IS_EXCEEDED(*result))
    {
        *result = 0;
        calc->status = RANGE_EXCEEDED;
    }

    if (SUCCESS == calc->status)
    {
	    StackPush(calc->stack[OPERAND], (void *)result);
    }
}


/*********************Calculation Functions***********************/
static calc_status_t SyntaxError(double lhs, double rhs, double *result)
{
    (void)lhs;
    (void)rhs;
    (void)result;
    return SYNTAX_ERROR;
}

static calc_status_t Add(double lhs, double rhs, double *result)
{
    *result = lhs + rhs;
    return SUCCESS;
}

static calc_status_t Sub(double lhs, double rhs, double *result)
{
    *result =  lhs - rhs;
    return SUCCESS;
}

static calc_status_t Mul(double lhs, double rhs, double *result)
{
    *result =  lhs * rhs;
    return SUCCESS;
}

static calc_status_t Div(double lhs, double rhs, double *result)
{
    if (0 == rhs)
    {
        *result = 0;
        return DIVISION_BY_ZERO;
    }
    *result =  lhs / rhs;
    return SUCCESS;
}

static calc_status_t Pow(double lhs, double rhs, double *result)
{
    *result = pow(lhs, rhs);
    return SUCCESS;
}

static calc_status_t OpenParan(double lhs, double rhs, double *result)
{
    *result = 0;
    (void)lhs;
    (void)rhs;
    return UNBALANCED_PARENTHESES;
}