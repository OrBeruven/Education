/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>      /*printf*/
#include <sys/types.h>  /*pid_t*/
#include <unistd.h>     /*fork, getppid, getpid*/
#include <signal.h>     /*kill*/

#define SUCCESS 0
#define FAIL 1

void SigUser2Handler(int signo);

int main(void)
{
    size_t count = 0;

    signal(SIGUSR2, SigUser2Handler);

    while (100 > count)
    {
        pause();
        sleep(1);
        write(1, "\t\t......PONG\n", 14);
        kill(getppid(), SIGUSR1);
        ++count;
    }

    return 0;
}

void SigUser2Handler(int signo)
{
    return;
}
