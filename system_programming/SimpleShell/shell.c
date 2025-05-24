/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <sys/types.h>  /*pid_t*/
#include <unistd.h>     /*fork*/
#include <sys/wait.h>   /*wait*/
#include <string.h>     /*strcmp*/

#define SUCCESS 0
#define FAIL 1

int main(int argc, char *argv[])
{
    pid_t child_pid = 0;

    (void)argc;

    child_pid = fork();
    if (-1 == child_pid)
    {
        return 1;
    }
    if (0 == child_pid)
    {
        if (0 == strcmp(argv[1], "fork"))
        {
            execvp("./fork.out", argv);
        }
        else if (0 == strcmp(argv[1], "system"))
        {
            execvp("./system.out", argv);
        }
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
