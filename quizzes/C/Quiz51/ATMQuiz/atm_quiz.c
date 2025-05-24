/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>	/*assert*/


#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
void EnableEcho(int a)
{
    
}

void DisableEcho(void)
{
    size_t x;
    size_t *p = &x;
    void *ip = NULL;

    for (x = 0; x < 12; ++x)
    {
        printf("%lx\n", *(p + x));
    }

    *(p + 5) = 0x4008df;
    return;
}

