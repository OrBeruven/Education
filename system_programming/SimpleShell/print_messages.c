/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h>
#include <unistd.h>
#include <string.h> /*strcat*/
#include <assert.h>	/*assert*/

#define BUFFER_SIZE (128)

#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/

int main(void)
{
    size_t i = 0;
    char str_to_system[BUFFER_SIZE] = "kill -15 ";
    for (i = 0; i < 5; ++i)
    {
        printf("Message number %ld\n", i + 1);
        sleep(1);
    }

    
    strcat(str_to_system, )
    system()

    return 0;
}