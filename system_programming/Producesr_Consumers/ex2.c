/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

    Compile with : gd ex2.c ../../ds/src/linked_list.c 

*****************************/
#include <pthread.h>    /*pthread*/
#include <stdio.h>      /*fgets*/

#include "../../ds/include/linked_list.h"
#include "../../ds/src/linked_list.c"

#define BUFFER 12
#define SUCCESS 0
#define FAIL 1

sll_t *sll = NULL;
pthread_mutex_t mutex;

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
void *Producers(void *arg);

void *Consumers(void *arg);
/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
int main(void)
{
    pthread_t consumer_thread[3];
    pthread_t producer_thread[3];

    sll = SLLCreate();
    pthread_create(&producer_thread[0], NULL, Producers, (void *)1);
    pthread_create(&producer_thread[1], NULL, Producers, (void *)10);
    pthread_create(&producer_thread[2], NULL, Producers, (void *)100);

    pthread_create(&consumer_thread[0], NULL, Consumers, (void *)1);
    pthread_create(&consumer_thread[1], NULL, Consumers, (void *)10);
    pthread_create(&consumer_thread[2], NULL, Consumers, (void *)100);

    pthread_join(producer_thread[0], NULL);
    pthread_join(producer_thread[1], NULL);
    pthread_join(producer_thread[2], NULL);
    
    pthread_join(consumer_thread[0], NULL);
    pthread_join(consumer_thread[1], NULL);
    pthread_join(consumer_thread[2], NULL);

    pthread_mutex_destroy(&mutex);
    SLLDestroy(sll);
    return 0;
}

/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
void *Producers(void *arg)
{
    size_t i = 1;
    
    while (3 >= i)
    {
        pthread_mutex_lock(&mutex);

        SLLInsertBefore(SLLEndIter(sll), (void *)(i * (size_t)arg));
        ++i;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *Consumers(void *arg)
{
    size_t i = 1;    
    (void)arg;

    while (3 >= i)
    {
        while (SLLIsEmpty(sll) || 0 != pthread_mutex_trylock(&mutex));

        printf("Consumer number %lu Consumed producer's number %lu\n", (size_t)arg, (size_t)SLLGetData(SLLBeginIter(sll)));
        SLLRemove(SLLBeginIter(sll));
        ++i;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
/*******************************************************************************

*******************************************************************************/