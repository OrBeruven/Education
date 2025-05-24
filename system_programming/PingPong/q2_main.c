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

void SigUser1Handler(int signo);

int main(void)
{
    pid_t child_pid = 0;
    size_t count = 0;
    char *args[2] = {NULL};
    char *file = "./q2_fork.out";
    pid_t ppid = getpid();

    signal(SIGUSR1, SigUser1Handler);

    

    child_pid = fork();
    if (-1 == child_pid)
    {
        return 1;
    }
    if (0 == child_pid)
    {
        execvp(file, args);
    }
    else
    {
        while (100 > count)
        {
            sleep(1);
            write(1, "PING......\n", 12);
            kill(child_pid, SIGUSR2);
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
