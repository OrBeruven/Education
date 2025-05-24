/***************
Name: Or Beruven
Tester:	Avri Kehat
Date Test: 21.01.2023
***************/

#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <stdio.h> /*using - printf, snprintf*/
#include <stdlib.h> /*using - malloc, free */
#include <assert.h> /*using - assert*/


typedef enum {SUCCESS = 0, FAILURE = 1, ALLOC_ERROR, MEMORY_ERROR} status_t;

typedef struct element_s element;

typedef void (*clean_up_t)(element*);
typedef status_t (*add_to_element_t)(element*, int);
typedef void (*print_element_t)(element*);

struct element_s
{
    void *value;
 
    add_to_element_t add_func;
    print_element_t print_func;
    clean_up_t clean_func;
};

void PrintIntElement(element *elem);
void PrintFloatElement(element *elem);
void PrintStrElement(element *elem);

status_t AddToInt(element *elem, int to_add);
status_t AddToFloat(element *elem, int to_add);
status_t AddToStr(element *elem, int to_add);

void CleanForNum(element *elem);
void CleanForStr(element *elem);



#endif
