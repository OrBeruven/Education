/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h> /*print*/
#include <signal.h>
#include <string.h> /*sprintf*/
#include <unistd.h> /* getpid*/
#include <stdlib.h> /*system*/

#define MAX_LINE_LENGTH 1024

static pid_t pong_pid = -1;

void PingHandler(int sig, siginfo_t *info, void *context);

int main ()
{
    struct sigaction sa;
    char command[MAX_LINE_LENGTH] = {0};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = PingHandler;

    sigaction(SIGUSR1, &sa, NULL);

    sprintf(command, "./q4_ping.out %d &", getpid());
    system(command);

    alarm(100);
    while(1)
    {
        pause();
        sleep(1);
        kill(pong_pid, SIGUSR2);
    }
    return 0;
}

void PingHandler(int sig, siginfo_t *info, void *context)
{
    if (SIGUSR1 == sig)
    {
        printf("Ping Received SIGUSR1 form Pong!\n");
        pong_pid = info->si_pid;
    }
}

