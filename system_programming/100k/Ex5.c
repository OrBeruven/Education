#include <stdio.h> /*print*/
#include <unistd.h>
#include <omp.h>    /*openMP*/

const size_t div = 12345678912;

int main ()
{
    size_t i = 0;
    size_t sum = 0;

    #pragma omp parallel reduction(+:sum)
    {
        /*printf("%d\n", omp_get_num_threads());*/
        #pragma omp for
        for (i = 1; i <= div; ++i)
        {
            if (0 == div % i)
            {
                sum += i;
            }
        }
    }

    printf("sum = %ld\n", sum);
    return 0;
}
