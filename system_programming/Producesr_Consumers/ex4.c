/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

    Compile With :  gd ex4.c ../../ds/src/fsq.c -I../../ds/include

*****************************/
#include <pthread.h>    /*pthread*/
#include <stdio.h>      /*fgets*/
#include <semaphore.h>  /*semaphore*/

#include "../../ds/include/fsq.h"

#define BUFFER (12)
#define SUCCESS (0)
#define FAIL (1)
#define FSQ_SIZE (10)

fsq_t *fsq = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_semaphore;
sem_t full_semaphore;

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

    fsq = FSQCreate(FSQ_SIZE);
    sem_init(&empty_semaphore, 0, FSQ_SIZE);
    sem_init(&full_semaphore, 0, 0);

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

    sem_destroy(&empty_semaphore);
    sem_destroy(&full_semaphore);
    pthread_mutex_destroy(&mutex);
    
    
    FSQDestroy(fsq);
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
        sem_wait(&empty_semaphore);
        pthread_mutex_lock(&mutex);
 
        FSQEnqueue(fsq, (int)(i * (size_t)arg));
        ++i;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_semaphore);
    }

    return NULL;
}

void *Consumers(void *arg)
{
    int i = 1; 
    (void)arg;

    while (3 >= i)
    {
        sem_wait(&full_semaphore);
        pthread_mutex_lock(&mutex);

        printf("Consumer number %lu Consumed producer's number %d\n", (size_t)arg, FSQPeek(fsq));
        FSQDequeue(fsq);
        ++i;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_semaphore);
    }

    return NULL;
}
/*******************************************************************************

*******************************************************************************/