/*****************************

   FORK

*****************************/
#include <stdio.h>      /*printf*/
#include <stdlib.h>     /*system*/
#include <string.h>     /*strcmp, strtok, strlen*/

#define SUCCESS (0)
#define FAIL (1)

#define BUFFER_SIZE (128)

int main(void)
{
    char input[BUFFER_SIZE] = {0};
    int return_status = 0;

    while (0 == return_status)
    {
        printf("\033[1m\033[30mberu@berupc:\033[31m~/Beru'sSimpleShell$ \033[0m");
        fgets(input, BUFFER_SIZE, stdin);
        input[strlen(input) - 1] = '\0';

        if (NULL != strstr(input, "exit"))
        {
            break;
        }
        return_status = system(input);
    }

    return return_status;
}
