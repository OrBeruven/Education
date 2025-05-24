/*****************************
	Name : Or Beruven

	Reviewed By : Lilach

	Date Test: 18.03.2023

	Description : header file for recursion

*****************************/

#ifndef RECURSION_H
#define RECURSION_H

#include <stddef.h>			/*size_t*/

#include "stack.h"
/**************************************************************
					Definitions
***************************************************************/
typedef struct node
{
	void *data;
	struct node *next;
} node_t;


/**************************************************************
					Function Declerations
***************************************************************/
int FiboIter(int n);

int FiboRec(int n);

node_t *SLLFlip(node_t *head);

stack_t *StackSort(stack_t *stack);

size_t StrLenRec(const char *s);

int StrCmpRec(const char *s1, const char *s2);

char *StrCpyRec(char *dest, const char *src);

char *StrCatRec(char *dest, const char *src);

char *StrStrRec(const char *haystack, const char *needle);

#endif
