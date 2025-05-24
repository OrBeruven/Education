/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For Watchdog Implemantation

*****************************/
#include <pthread.h>            /*pthread_t*/
#include <stdio.h>              /*perror*/
#include <stdlib.h>             /*setenv, getenv*/
#include <signal.h>             /*sigaction*/
#include <stdatomic.h>          /*_Atomic*/
#include <assert.h>	            /*assert*/
#include <semaphore.h>          /*sem_t*/
#include <fcntl.h>              /*O_CREAT*/
#include <sys/types.h>          /*fork, wait, pid_t*/
#include <unistd.h>             /*fork*/
#include <sys/wait.h>           /*wait*/
#include "../include/sched.h"   /*For removing red lines *//*giving full path so the vscode recognize it*/
#include "watchdog.h"           /*scheduler*/

#ifndef NDEBUG
#define PRINT_DEBUG(...) (printf(__VA_ARGS__))
#else
#define PRINT_DEBUG(...)
#endif

#define ERR_HANDL(value, expected_value, func_name, return_status) if((expected_value) == (value))  \
                                                                    {	perror(#func_name);	        \
                                                                        return return_status;       \
                                                                    }

#define SUCCESS (0)
#define FAIL (1)
#define SYS_FAIL (-1)
#define CHECK_INTERVAL (2)
#define SEND_SIGNAL_INTERVAL (1)
#define VAR_BUFFER (10)

#define SEM_NAME ("/sync_two_processes")
#define WD_ENV ("WD_PID")
#define THRSH_ENV ("THRSH_HLD")
#define WD_FILE ("./bin/watchdog.out")

typedef enum is_wd {ISNT_WD = 0, IS_WD = 1}is_wd_t;

typedef enum scheduler_status
{
    SUCCESS_EXIT = 0,
    FAILURE_EXIT = -1,
    RESUS_EXIT = 1,
    STOP_EXIT = 2
}scheduler_status_t;

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/

static int SetWDElements(size_t threshold);
static int CreateThreadInProcess(char *argv[]);
static int LoadScheduler(sch_t *sch, size_t threshhold);
static void *StartRoutine(void *arg);

/*******************************************************************************
                    Signal Handlers Declarations
*******************************************************************************/

void SigUsr1Handler(int sig);
void SigUsr2Handler(int sig);

/*******************************************************************************
                    Scheduler Function Declarations
*******************************************************************************/

scheduler_status_t SendSignal(void *arg);
scheduler_status_t CheckCounter(void *threshold);

/*******************************************************************************
*******************************************************************************/

_Atomic int atomic_counter = 0;
_Atomic int stop_flag = 0;
is_wd_t wd_flag = ISNT_WD;
static char **argv_for_thread = NULL;
static sem_t *sync_semaphore = NULL;
static sch_t *scheduler = NULL;
static pid_t target_pid;
static pthread_t user_worker_thread;
static pthread_mutex_t pid_mutex = PTHREAD_MUTEX_INITIALIZER;

struct sigaction su1;
struct sigaction su2;
/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
int MakeMeImmortal(size_t threshold , int argc, char *argv[])
{
    pid_t pid;
    
    assert(NULL != argv);
    (void)argc;

    argv_for_thread = argv;

    ERR_HANDL(SetWDElements(threshold), FAIL, ,FAIL);

    if (ISNT_WD == wd_flag)
    {
        pid = fork();
        ERR_HANDL(pid, SYS_FAIL, fork, FAIL);

        if (0 == pid)
        {
            execvp(WD_FILE, argv);
        }
        else
        {
            pthread_mutex_lock(&pid_mutex);
            target_pid = pid;
            pthread_mutex_unlock(&pid_mutex);

            if (FAIL == LoadScheduler(scheduler, threshold))
            {
                SchDestroy(scheduler);
                return FAIL;
            }

            if (FAIL == CreateThreadInProcess(argv))
            {
                SchDestroy(scheduler);
                return FAIL;
            }   

        }
    }
    else 
    {
        /*Watchdog section : */
        pthread_mutex_lock(&pid_mutex);
        target_pid = getppid();
        pthread_mutex_unlock(&pid_mutex);

        ERR_HANDL(kill(target_pid, SIGCONT), SYS_FAIL, kill, FAIL);
        ERR_HANDL(LoadScheduler(scheduler, threshold), FAIL, , FAIL);
        ERR_HANDL(sem_post(sync_semaphore), SYS_FAIL, sem_post, FAIL);

        if (RESUS_EXIT == SchRun(scheduler))
        {
            SchDestroy(scheduler);
            ERR_HANDL(sem_unlink(SEM_NAME), SYS_FAIL, sem_unlink, FAIL);
            execvp(argv[0], argv);
        }
        else
        {
            SchDestroy(scheduler);
        }
    }

    return SUCCESS;
}

int DoNotResuscitate()
{
    ERR_HANDL(kill(target_pid, SIGUSR2), SYS_FAIL, kill, FAIL);
    ERR_HANDL(raise(SIGUSR2), SYS_FAIL, raise, FAIL);

    ERR_HANDL(sem_close(sync_semaphore), SYS_FAIL, sem_close, FAIL);
    ERR_HANDL(sem_unlink(SEM_NAME), SYS_FAIL, sem_unlink, FAIL);

    ERR_HANDL(!pthread_join(user_worker_thread, NULL), SUCCESS, pthread_join, FAIL);

    SchDestroy(scheduler);
    ERR_HANDL(wait(NULL), SYS_FAIL, wait, FAIL);
    ERR_HANDL(unsetenv(THRSH_ENV), SYS_FAIL, unsetenv, FAIL);

    return SUCCESS;
}
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
static int SetWDElements(size_t threshold)
{
    char thresh_buffer[VAR_BUFFER] = {0};

    sprintf(thresh_buffer, "%lu", threshold);
    ERR_HANDL(setenv(THRSH_ENV, thresh_buffer, 0), SYS_FAIL, , FAIL);

    su1.sa_handler = SigUsr1Handler;
    ERR_HANDL(sigaction(SIGUSR1, &su1, NULL), SYS_FAIL, ,FAIL);

    su2.sa_handler = SigUsr2Handler;
    ERR_HANDL(sigaction(SIGUSR2, &su2, NULL), SYS_FAIL, ,FAIL);

    sync_semaphore = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    ERR_HANDL(sync_semaphore, SEM_FAILED, ,FAIL);

    scheduler = SchCreate();
    ERR_HANDL(scheduler, NULL, , FAIL);

    return SUCCESS;
}

static int CreateThreadInProcess(char *argv[])
{
    ERR_HANDL(!pthread_create(&user_worker_thread, NULL, StartRoutine, (void *)argv), SUCCESS, pthread_create, FAIL);
    return SUCCESS;
}

static int LoadScheduler(sch_t *sch, size_t threshhold)
{
    if (UIDIsSame(UIDGetBad(), SchAddTask(sch, SendSignal, NULL, time(NULL), SEND_SIGNAL_INTERVAL)))
    {
        return FAIL;
    }

    if (UIDIsSame(UIDGetBad(), SchAddTask(sch, CheckCounter, (void *)threshhold, time(NULL), CHECK_INTERVAL)))
    {
        return FAIL;
    }

    return SUCCESS;
}

static int CreateWD(void)
{
    pid_t pid;
	pid = fork();

    ERR_HANDL(pid, SYS_FAIL, fork, FAIL);
	if (0 == pid)
	{
		execvp(WD_FILE, argv_for_thread);
		perror("execvp()");
		return FAIL;
	}

    ERR_HANDL(!raise(SIGSTOP), SUCCESS, raise, FAIL);

    pthread_mutex_lock(&pid_mutex);
    target_pid = pid;
    pthread_mutex_unlock(&pid_mutex);
	return SUCCESS;
}

static void *StartRoutine(void *argv)
{
    (void)argv;

    ERR_HANDL(sem_wait(sync_semaphore), SYS_FAIL, sem_wait, NULL);
    SchRun(scheduler);

    return NULL;
}
/*******************************************************************************
                    Scheduler Function Implementation
*******************************************************************************/
scheduler_status_t SendSignal(void *arg)
{
    (void)arg;
    if (!stop_flag)
    {
        PRINT_DEBUG("send signal to %d\n", target_pid);

        ERR_HANDL(kill(target_pid, SIGUSR1), SYS_FAIL, kill, FAILURE_EXIT);
        ++atomic_counter;

        return SUCCESS_EXIT;
    }
    else
    {
        return STOP_EXIT;
    }
}

scheduler_status_t CheckCounter(void *threshold)
{
    PRINT_DEBUG("checking counter = %d, threshold %lu\n", atomic_counter, (size_t)threshold);
    if ((size_t)threshold < (size_t)atomic_counter)
    {
        if (ISNT_WD == wd_flag)
        {
            ERR_HANDL(wait(NULL) , SYS_FAIL, wait, EXIT_FAILURE);
            ERR_HANDL(CreateWD(), SYS_FAIL, CreateWD, EXIT_FAILURE);
            atomic_counter = 0;
        }
        else
        {
            ERR_HANDL(raise(SIGUSR2), SYS_FAIL, raise, EXIT_FAILURE);
            return RESUS_EXIT;
        }
    }

    return SUCCESS_EXIT;
}

/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
                    Signal Handlers Implementation
*******************************************************************************/
void SigUsr1Handler(int sig)
{
    if (SIGUSR1 == sig)
    {
        PRINT_DEBUG("Got signal %d\n", target_pid);
        atomic_counter = 0;
    }
}

void SigUsr2Handler(int sig)
{
    if (SIGUSR2 == sig)
    {
        ++stop_flag;
    }
}
/*******************************************************************************
*******************************************************************************/