#include <pthread.h> /*pthread_create*/
#include <stdio.h> /*print*/
#include <unistd.h>

#define THREAD_SIZE (10)

void *SetArray(void *arg);

const size_t div = 12345678912;
int s[THREAD_SIZE] = {0};

int main ()
{
    size_t i = 0;
    pthread_t threads[THREAD_SIZE];
    size_t sum = 0;
    void *return_value = 0;
    size_t range = div / THREAD_SIZE + 1;

    for (i = 0; i < THREAD_SIZE && range < div + div / THREAD_SIZE + 1; ++i, range += div / THREAD_SIZE + 1)
    {
        pthread_create(&threads[i], NULL, SetArray, (void *)(range));
    }
   
    for (i = 0; i < THREAD_SIZE; ++i)
    {
        /*printf("%d-%ld, ", s[i], i);*/
        pthread_join(threads[i], &return_value);
        sum += (size_t)return_value;
    }

    printf("sum = %ld\n", sum);
    return 0;
}

void *SetArray(void *arg)
{
    size_t sum_of_divisors = 0;
    size_t range = (size_t)arg;
    size_t index = range - (div / THREAD_SIZE + 1) + 1;

    for (; index < range; ++index)
    {
        if (0 == div % index)
        {
            sum_of_divisors += index;
        }
    }

    return (void *)sum_of_divisors;
}
