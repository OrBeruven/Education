/***************
Name: Or Beruven
Tester:	Avri Kehat
Date Test: 21.01.2023
***************/

#include <string.h> /*using - strlen */

#include "elements.h"

/*sub function to AddToStr*/
static int CountDigits(int num);

/*print functions for elements*/
void PrintIntElement(element *elem)
{
	assert(NULL != elem);
	printf("The integer number in the Element : %ld\n", (long int)elem->value);
	return;
}

void PrintFloatElement(element *elem)
{
	assert(NULL != elem);
	printf("The float number in the Element : %f\n", *(float *)&elem->value);
	return;
}

void PrintStrElement(element *elem)
{
	assert(NULL != elem);
	printf("The value is str : %s\n", (char *)elem->value);
	return;
}


/*add functions for elements */
status_t AddToInt(element *elem, int to_add)
{
	assert(NULL != elem);
	elem->value = (void *)((long int)elem->value + to_add);
	return SUCCESS;
}

status_t AddToFloat(element *elem, int to_add)
{
	assert(NULL != elem);
	*(float *)&elem->value += to_add;
	return SUCCESS;
}

status_t AddToStr(element *elem, int to_add)
{
	assert(NULL != elem);
	
	elem->value = realloc((char *)elem->value, sizeof(char) * (strlen(elem->value) + 1 + CountDigits(to_add)));
	if(NULL == elem->value)
	{
		printf("An error while allocating\n");
		return ALLOC_ERROR;
	}
	
	/*return negative in case of failure */
	if( 0 > sprintf(elem->value, "%s%d", (char *)elem->value, to_add))
	{
		printf("writing error\n");
		return MEMORY_ERROR;
	}

	return SUCCESS;
}

static int CountDigits(int num)
{
	int count = 0;
	
	while (0 < num)
	{
		num /= 10;
		++count;
	}
	
	return count;
}

/*clean (free) functions for elements */
void CleanForNum(element *elem)
{
	assert(NULL != elem);
	/*empty on purpose*/
	(void)elem;
	return;
}

void CleanForStr(element *elem)
{
	assert(NULL != elem);
	free(elem->value);
	return;
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

