/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>  /*printf*/
#include <pthread.h>   
#include <stdlib.h>
#include <assert.h>	/*assert*/


#define SUCCESS 0
#define FAIL 1

int global = 2;
__thread int tls;

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
void *mapping(void *a);
/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
int main(void)
{
    pthread_t thread;
    pthread_create(&thread, NULL, mapping, NULL);

    pthread_join(thread, NULL);

    return 0;
}

/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
void *mapping(void *a)
{
    int *heap_var = NULL;
    (void)a;
    heap_var = (int *)malloc(sizeof(int));

    printf("Adress of global: %p\n", (void *)&global);      /*found in data/text*/
    printf("Adress of tls \t: %p\n", (void *)&tls);         /*stack of the thread*/
    printf("Adress of heap \t: %p\n", (void *)heap_var);    /*heap of the thread*/

    free(heap_var);
    return NULL;
}

/*******************************************************************************

*******************************************************************************/

/* global  : 0x555555558010
tls 	: 0x7ffff7bff63c
 heap 	: 0x7ffff0000b70 */
