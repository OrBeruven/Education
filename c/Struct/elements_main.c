/***************
Name: Or Beruven
Tester:	Avri Kehat
Date Test: 21.01.2023
***************/

#include "elements.h"

#define ELEMENTS_SIZE 3

#define MAX2(A,B) (( (A) > (B) ) ? (A) : (B) )
/*can impelemt MAX2 macro in MAX3 */
#define MAX3(A,B,C) ((MAX2(C,MAX2(A,B))))
/*#define MAX3(a,b,c) (( (a) > (b) ) ? ((a) > (c) ? (a) : (b)) : ((b) > (c) ? (b) : (c) ))*/
#define SIZEOF_VAR(VAR) (char *)(&VAR + 1) - (char *)(&VAR)
#define SIZEOF_TYPE(TYPE) (long)(1 + ((TYPE*)0))

static void PrintElementArrTest(element *elem_arr)
{
	int i = 0;
	
	assert(NULL != elem_arr);
	
	for (i = 0; i < ELEMENTS_SIZE; ++i)
	{
		elem_arr[i].print_func(&elem_arr[i]);
	}
	
	return;
}

static void AddToElementsTest(element *elem_arr)
{
	int i = 0;
	long int answer = 0;
	
	assert(NULL != elem_arr);
	
	printf("Enter an integer to add : ");
	scanf("%ld", &answer);
	printf("\n");
	
	for(i = 0; i < ELEMENTS_SIZE; ++i)
	{
		if (SUCCESS != elem_arr[i].add_func(&elem_arr[i], answer))
		{
			printf("An error occurred\n");
		}
	}
	
	return;
}

static void CleanElementArrTest(element *elem_arr)
{
	int i = 0;
	
	assert(NULL != elem_arr);
	
	for(i = 0; i < ELEMENTS_SIZE; ++i)
	{
		elem_arr[i].clean_func(&elem_arr[i]);
	}
	
	return;
}

static void MacroTest()
{
	int a = 1;
	int b = 3;
	int c = 2;
	
	printf("The bigger number is : %d\n", (int)MAX2(a,c));
	printf("The bigger number is : %d\n", (int)MAX3(a,b,c));
	
	printf("Sizeof Var : %ld\n", SIZEOF_VAR(c));
	printf("Sizeof type : %ld\n", SIZEOF_TYPE(float));	
	return;
}

int main(void)
{
	/*elements type*/
	long int x = 5;
	char *str = NULL;
	float f = 4.2;
	
	/*declare array*/
	element elem_arr[ELEMENTS_SIZE] = { {NULL, AddToStr, PrintStrElement, CleanForStr},
								{NULL, AddToInt, PrintIntElement, CleanForNum}, 
								{NULL, AddToFloat, PrintFloatElement, CleanForNum} };
	
	/*initialize string arr[0]*/
	str = (char *)malloc(sizeof(char) * 4);
	assert(NULL != str);
	
	sprintf(str, "abc");
	elem_arr[0].value = str;
	
	/*initialize float arr[1]*/
	elem_arr[1].value = (void *)x;

	/*initialize integer arr[2]*/
	*(float *)&elem_arr[2].value = f;

	
	/*tests to the elements.c functions*/
	PrintElementArrTest(elem_arr);
	AddToElementsTest(elem_arr);
	PrintElementArrTest(elem_arr);
	AddToElementsTest(elem_arr);
	PrintElementArrTest(elem_arr);
	CleanElementArrTest(elem_arr);
	
	MacroTest();
	
	
	return 0;
}
	
