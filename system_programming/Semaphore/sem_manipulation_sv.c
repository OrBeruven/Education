/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>      /*printf*/
#include <stdlib.h>     /*exit*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>    /*PV4 semaphore*/
#include <sys/sem.h>
#include <sys/stat.h>
#include <string.h>     /*strtok. strlen*/

#define COMMAND_BUFFER (64)
#define MAX_TOKEN (3)
#define UNDO_SIZE (6)

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
static void GetCommand(char *command, char **args);
/*******************************************************************************

*******************************************************************************/

int main(void) 
{
    key_t key;
    int semid;
    struct sembuf op;

    int value = 0;
    char command[COMMAND_BUFFER] = {0};
    char *args[MAX_TOKEN] = {NULL};

    key = ftok("/home/beru/BeruEnv/or.beruven/system_programming/Semaphore/key.txt", 's');
    if (-1 == key) 
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (-1 == semid) 
    {
        semid = semget(key, 1, IPC_CREAT | 0666);
        if (-1 == semid) 
        {
            perror("semget");
            exit(EXIT_FAILURE);
        }
    }

    op.sem_num = 0;

    while (1)
    {
        GetCommand(command, args);

        switch (*args[0])
        {
            case 'X':
                exit(0);
                break;
            
            case 'V':
                value = semctl(semid, 0, GETVAL);
                if (-1 == value)
                {
                    perror("semctl");
                    exit(EXIT_FAILURE);
                }
                printf("Value of the semaphore is %d\n", value);
                break;

            case 'D':
            case 'I':
                value = ('I' == *args[0] ? atoi(args[1]) : -atoi(args[1]));
                op.sem_op = value;
                op.sem_flg = (NULL != args[2] && 0 == strncmp(args[2], "[undo]", UNDO_SIZE)) ? SEM_UNDO : IPC_NOWAIT;
                
                if (-1 == semop(semid, &op, 1)) 
                {
                    perror("semop");
                    exit(EXIT_FAILURE);
                }
                break;

            default:
                break;
        }
    }

    return 0;
}

static void GetCommand(char *command, char **args)
{
    size_t i = 0;
    char *token = NULL;

    fgets(command, COMMAND_BUFFER, stdin);
    command[strlen(command) - 1] = '\0';
    token = strtok(command, " ");

    while (NULL != token)
    {
        args[i] = token;
        ++i;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}