/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

    Compile With : gd ex3.c ../../ds/src/linked_list.c

*****************************/
#include <pthread.h>    /*pthread*/
#include <stdio.h>      /*fgets*/
#include <semaphore.h>  /*semaphore*/

#include "../../ds/include/linked_list.h"

#define BUFFER 12
#define SUCCESS 0
#define FAIL 1

sll_t *sll = NULL;
pthread_mutex_t mutex;
sem_t sem;

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
    pthread_t consumer_thread[4];
    pthread_t producer_thread[4];

    sll = SLLCreate();
    sem_init(&sem, 0, 1);

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

    sem_destroy(&sem);
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
        sem_post(&sem);

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
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);

        printf("Consumer number %lu Consumed producer's number %lu\n", (size_t)arg, (size_t)SLLGetData(SLLBeginIter(sll)));
        SLLRemove(SLLBeginIter(sll));
        ++i;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
/*******************************************************************************

*******************************************************************************/