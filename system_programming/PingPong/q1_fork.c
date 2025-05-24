/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/

#include <stdio.h>      /*printf*/
#include <sys/types.h>  /*pid_t*/
#include <unistd.h>     /*fork, getppid, getpid*/
#include <sys/wait.h>   /*wait*/
#include <string.h>     /*strcmp*/
#include <signal.h>     /*kill*/

#define SUCCESS 0
#define FAIL 1

void SigUser1Handler(int signo);
void SigUser2Handler(int signo);

int main(void)
{
    pid_t child_pid = 0;
    size_t count = 0;
    signal(SIGUSR1, SigUser1Handler);
    signal(SIGUSR2, SigUser2Handler);

    
    child_pid = fork();
    if (-1 == child_pid)
    {
        return 1;
    }
    if (0 == child_pid)
    {
        while (10 > count)
        {
            pause();
            sleep(1);
            write(1, "\t\t......PONG\n", 14);
            kill(getppid(), SIGUSR2);
            ++count;
        }
    
    }
    else
    {
        while (10 > count)
        {
            sleep(1);
            write(1, "PING......\n", 12);
            kill(child_pid, SIGUSR1);
            pause();
            ++count;
        }
    }
    

    return 0;
}

void SigUser1Handler(int signo)
{
    return;
}

void SigUser2Handler(int signo)
{
    return;
}