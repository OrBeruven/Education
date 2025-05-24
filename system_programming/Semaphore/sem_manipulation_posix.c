/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h> /*strlen, strtok, strncmp*/

#define SUCCESS 0
#define FAIL 1

#define SEM_NAME_BUFFER (64)
#define COMMAND_BUFFER (64)
#define MAX_TOKEN (3)
#define UNDO_SIZE (6)

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
void SemaphoreAdjusment(sem_t *sem, int adjusment_value);
/*******************************************************************************

*******************************************************************************/
int main(void) 
{
    size_t i = 0;
    sem_t *sem;
    int value = 0;
    int undo_adjusment = 0;

    char sem_name[SEM_NAME_BUFFER] = {0};
    char command[COMMAND_BUFFER] = {0};
    char *args[MAX_TOKEN] = {NULL};
    char *token = NULL;

    fgets(sem_name, SEM_NAME_BUFFER, stdin);
    sem_name[strlen(sem_name) - 1] = '\0';

    sem = sem_open(sem_name, O_CREAT, 0666, 0);
    if (SEM_FAILED == sem) 
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        value = 0;
        token = NULL;
        i = 0;

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

        if (NULL != args[1])
        {
            value = atoi(args[1]);
        }

        switch (*args[0])
        {
            case 'X':
                SemaphoreAdjusment(sem, undo_adjusment);
                
                if (-1 == sem_close(sem)) 
                {
                    perror("sem_close");
                    exit(EXIT_FAILURE);
                }

                exit(0);
                break;
            
            case 'V':
                if (-1 == sem_getvalue(sem, &value)) 
                {
                    perror("sem_getvalue");
                    exit(EXIT_FAILURE);
                }
                printf("Value of the semaphore is %d\n", value);
                break;

            case 'I':
                if (NULL != args[2] && NULL != strstr(args[2], "[undo]"))
                {
                    undo_adjusment += value;
                }

                while (0 < value)
                {
                    if (-1 == sem_post(sem)) 
                    {
                        perror("sem_post");
                        exit(EXIT_FAILURE);
                    }
                    --value;
                }
                break;

            case 'D':
                if (NULL != args[2] && 0 == strncmp(args[2], "[undo]", UNDO_SIZE))
                {
                    undo_adjusment -= value;
                }

                while (0 < value)
                {
                    if (-1 == sem_wait(sem)) 
                    {
                        perror("sem_wait");
                        exit(EXIT_FAILURE);
                    }
                    --value;
                }
                break;


            default:
                break;
        }
    }
    
    return 0;
}

/*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
void SemaphoreAdjusment(sem_t *sem, int adjusment_value)
{
    while (0 < adjusment_value)
    {
        if (-1 == sem_wait(sem)) 
        {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        --adjusment_value;
    }

    while (0 > adjusment_value)
    {
        if (-1 == sem_post(sem)) 
        {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        ++adjusment_value;
    }
}
/*******************************************************************************

*******************************************************************************/