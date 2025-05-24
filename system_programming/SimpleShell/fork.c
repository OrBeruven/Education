/*****************************

   FORK

*****************************/
#include <stdio.h>      /*printf*/
#include <sys/wait.h>   /*wait*/
#include <string.h>     /*strcmp, strtok, strlen*/
#include <sys/types.h>  /*pid_t*/
#include <unistd.h>     /*fork*/

#define SUCCESS (0)
#define FAIL (1)

#define SMALL_BUFFER (128)
#define BUFFER_SIZE (512)
#define MAX_COMMAND (7)

int main(void)
{
    char input[BUFFER_SIZE] = {0};
    char *token = NULL;
    char *argv[MAX_COMMAND] = {NULL};

    int child_status = 0;

    size_t i = 0;
    pid_t child_pid = 0;

    while (0 == child_status)
    {
        i = 0;
        token = NULL;

        printf("\033[1m\033[30mberu@berupc:\033[31m~/Beru'sSimpleShell$ \033[0m");
        fgets(input, BUFFER_SIZE, stdin);
        input[strlen(input) - 1] = '\0';
        token = strtok(input, " ");

        while (NULL != token)
        {
            argv[i] = token;
            ++i;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL;

        if (0 == strcmp(argv[0], "exit"))
        {
            break;
        }

        child_pid = fork();

        if (0 == child_pid)
        {
            execvp(argv[0], argv);
        }
        else
        {
            wait(&child_status);
        }
    }

    return child_status;
}
