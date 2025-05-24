/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

    Compile With :  gd ex6.c

*****************************/
#include <pthread.h>    /*pthread*/
#include <stdio.h>      /*fgets*/
#include <semaphore.h>  /*semaphore*/

#define BUFFER (12)
#define SUCCESS (0)
#define FAIL (1)
#define CONSUMERS (3)

int data = 0;
int consumer_count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

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
    size_t i = 0;
    pthread_t consumer_thread[CONSUMERS];
    pthread_t producer_thread;
    
    sem_init(&sem, 0, 0);

    pthread_create(&producer_thread, NULL, Producers, (void *)1);

    for (i = 0; i < CONSUMERS; ++i)
    {
        pthread_create(&consumer_thread[i], NULL, Consumers, (void *)i);
    }

    for (i = 0; i < CONSUMERS; ++i)
    {
        pthread_join(consumer_thread[i], NULL);
    }

    pthread_join(producer_thread, NULL);

    sem_destroy(&sem);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cv);
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
    size_t j = 0;

    (void)arg;    
    while (5 >= i)
    {
        for (j = 0; j < CONSUMERS; ++j)
		{
			sem_wait(&sem);
		}

		pthread_mutex_lock(&mutex);

		++data;
        ++i;

		pthread_mutex_unlock(&mutex);
		pthread_cond_broadcast(&cv);

		for (j = 0; j < CONSUMERS; ++j)
		{
			sem_wait(&sem);
		}
		for (j = 0; j < CONSUMERS; ++j)
		{
			pthread_cond_signal(&cv);
        }
    }

    return NULL;
}

void *Consumers(void *arg)
{
    int i = 1; 
    (void)arg;

    while (5 >= i)
    {
        pthread_mutex_lock(&mutex);
        sem_post(&sem);
        pthread_cond_wait(&cv, &mutex);

        printf("Consumer number %lu Consumed producer's number %d\n", (size_t)arg, data);
        ++i;

        sem_post(&sem);
        pthread_cond_wait(&cv, &mutex);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
/*******************************************************************************

*******************************************************************************/
