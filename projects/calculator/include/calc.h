/*****************************
	Name : Or Beruven

	Reviewed By : Moshe

	Date Test: 07.04.2023

	Description : header file for calculator

*****************************/
#ifndef __ILRD__OL13940_CALCULATOR__
#define __ILRD__OL13940_CALCULATOR__

#include <stddef.h>

typedef struct calculator calc_t;

typedef enum calc_status
{
	SUCCESS = 0,
	SYNTAX_ERROR = 1,
	UNBALANCED_PARENTHESES = 2,
	DIVISION_BY_ZERO = 3,
	RANGE_EXCEEDED = 4,
	EXPRESSION_EXCEEDED = 5
} calc_status_t;

/*
* CalcCreate Description:
*	Creates a new Calculator.
*	 											
* @params:
*	max_exp - Maximum string length calculator can receive as input.
*
* @returns:
*	Pointer to calculator. In case of error returns NULL.
*
* @Complexity
*	O(1)
*/
calc_t *CalcCreate(size_t max_exp);

/*
* Calculator Description:
*	Calculates a mathematical expression composed of constants supplied as a string.
*
* @params:
*	calc - Calculator.
*   expression - Mathematical expression represeted as a string.
*   result - Pointer to a double type, returns result of calculation.
*   If the pointers are invalid - behavior is undefined.
*
* @returns:
*	calc_status_t - 0 in case of success.
*					Non-zero in case of error.
*
* @Complexity
*	O(n)
*/
calc_status_t Calculator(calc_t *calc, const char *expression, double *result);

/*
* CalcDestroy Description:
* 	Deallocates a given Calculator from memory.
* 
* @params:
*	calc - Pointer to a Calculator.
* 	If the pointer is invalid - behavior is undefined.
*
* @returns:
*	None
*
* @Complexity
*	O(1)
*/
void CalcDestroy(calc_t *calc);


#endif