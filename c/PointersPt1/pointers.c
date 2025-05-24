/*	A function that swaps two variables*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*	A function that swaps two variables*/
void Swap(int *a, int *b);
void SwapTmp(int *a, int *b);

/*	A function that makes a copy of array */
int* CpyArr(int *a, int num);

/*	A function that print address	*/
void PrintAdress(void *a);

/*Swap two size_t variables*/
void SwapT(size_t *a, size_t *b);

/*swap two size_t pointers*/
void SwapTP(size_t **a, size_t **b);

/*swap two size_t pointers using func1*/
void SwapTPV(size_t **a, size_t **b);



/*	Tester	*/
int main(void)
{
	size_t a = 5;
	size_t b = 10;
	size_t *a_ptr = &a;
	size_t *b_ptr = &b;
	
	
	/*	Print values and addresses before SwapT function	*/
	printf("before SwapT - a = %ld, b = %ld\nThe adresses are - a = %p, b = %p\n"
								, a, b, (void *)&a, (void *)&b);
	SwapT(&a, &b);
	printf("after SwapT - a = %ld, b = %ld\nThe adresses are - a = %p, b = %p\n"
								, a, b, (void *)&a, (void *)&b);




	/*	Print values and addresses before SwapTP function	*/
	printf("\nbefore SwapTP - a = %ld, b = %ld\nThe adresses are - a = %p, b = %p\n"
									, *a_ptr, *b_ptr, (void *) a_ptr, (void *) b_ptr);
	SwapTP(&a_ptr, &b_ptr);
	printf("after SwapTP - a = %ld, b = %ld\nThe adresses are - a = %p, b = %p\n"
									, *a_ptr, *b_ptr, (void *) a_ptr, (void *) b_ptr);
	
	
	
	
	/*	Print values and addresses before SwapTPV function	*/
	printf("\nbefore SwapTPV - a = %ld, b = %ld\nThe adresses are - a = %p, b = %p\n"
									, a, b, (void *) a_ptr, (void *) b_ptr);
	SwapTPV(&a_ptr, &b_ptr);
	printf("after SwapTPV - a = %ld, b = %ld\nThe adresses are - a = %p, b = %p\n"
											 , a, b, (void *) a_ptr, (void *) b_ptr);
	return 0;
}

/*	A function that swaps two variables without using temp variable*/
void Swap(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

/*	A function that swaps two variables using temp variable*/
void SwapTmp(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*	A function which gets array pointer and size
	makes a copy of that array using allocation
	and returns a pointer					*/
int* CpyArr(int *a, int num)
{
	int *to_ret = (int *)malloc(sizeof(int) * num);
	int i = 0;
	
	/*	In gd compiler the decleration must come first
		therefore assert comes here					*/
	if((NULL == a) || (NULL == to_ret))	/* checking validation of memory */
	{
		printf("NULL pointer error!");
		return NULL;
	}

	for(i = 0; i < num; i++)
	{
		*(to_ret+i) = *(a+i);
	}
	
	
	return to_ret;
}

/*	Gets a pointer to which we'll print address	*/
void PrintAdress(void *a)
{
	printf("The adress of a give pointer is %p \n", a);
}

/*	Swap two size_t variables by their actual value					*/
void SwapT(size_t* a, size_t* b)
{
	size_t temp = *a;
	*a = *b;
	*b = temp;
}

/*	Swap two size_t pointers by their value (change a&b addresses)	*/
void SwapTP(size_t **a, size_t **b)
{
	size_t *temp = *a;
	*a = *b;
	*b = temp;
}

/*	Swap two size_t pointers using func1, change a&b values			*/
void SwapTPV(size_t **a, size_t **b)
{
	/*	Swap addresses	*/
	SwapT((size_t *) a, (size_t *) b);
	
	/*	Swap values - not needed		*/
	/*SwapT(*a,  *b);*/
}	

