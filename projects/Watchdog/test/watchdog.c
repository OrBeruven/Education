/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h> /*print*/
#include <stdlib.h> /*atoi, getenv, setenv*/
#include <signal.h> /*signals*/
#include <unistd.h> /* getpid fork */
#include <sys/types.h> /*pid_t*/

#include <semaphore.h>  /*sem_t*/
#include <fcntl.h>      /*O_EXCL, O_CREAT*/

#include "watchdog.h"

#define SUCCESS 0
#define FAIL 1

#define CHECK_INTERVAL 3
#define SEND_SIGNAL_INTERVAL 1

#define SEM_NAME "/sync_two_processes"
#define THRSH_ENV ("THRSH_HLD")

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/

/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
int main(int argc, char *argv[])
{
    int threshold = atoi(getenv(THRSH_ENV));
    extern int wd_flag;
    wd_flag = 1;

/*     printf("This is the watchdog speaking, threshold is : %d\n", threshold);
 */    MakeMeImmortal(threshold , argc, argv);

    return 0;
}

/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
