/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <pthread.h>    /*pthread*/
#include <stdlib.h>     /*atoi*/
#include <stdio.h>      /*fgets*/
#include <assert.h>	    /*assert*/
#include <stdatomic.h>  /*atomic*/

#define BUFFER 12
#define SUCCESS 0
#define FAIL 1

char buff[BUFFER] = {0};
atomic_int atomic_lock = 0;
/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
void *Producer(void *arg);

void *Consumer(void *arg);
/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
int main(void)
{
    pthread_t consumer_thread;
    pthread_t producer_thread;

    buff[10] = '\0';
    pthread_create(&consumer_thread, NULL, Consumer, NULL);
    pthread_create(&producer_thread, NULL, Producer, NULL);

    pthread_join(consumer_thread, NULL);
    pthread_join(producer_thread, NULL);
    return 0;
}

/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
void *Producer(void *arg)
{
    size_t i = 1;
    (void)arg;

    while (123456798 >= i)
    {
        while (1 == atomic_lock);
        
        sprintf(buff, "%ld", i);
        ++i;

        ++atomic_lock;
    }

    return NULL;
}

void *Consumer(void *arg)
{
    size_t i = 1;
    (void)arg;

    while (123456798 >= i)
    {
        while (0 == atomic_lock);
        
        printf("%s \n", buff);
        ++i;

        --atomic_lock;
    }

    return NULL;
}
/*******************************************************************************

*******************************************************************************/