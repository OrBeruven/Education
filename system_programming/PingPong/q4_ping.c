#include <sys/types.h> /*pid_t*/
#include <stdio.h> /*print*/
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> /*execpv*/

void PongHandler(int sig);

int main (int argc, char *argv[])
{
    int pong_pid = atoi(argv[1]);
    signal(SIGUSR2, PongHandler);
    
    while (1)
    {
        kill(pong_pid, SIGUSR1);
        pause();
        sleep(1);
    }
    return 0;
}

void PongHandler(int sig)
{
    if (sig == SIGUSR2)
    {
        printf("Pong Received SIGUSR2 from Ping!\n");
    }
}
