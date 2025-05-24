#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void ParentHandler(int sig);
void ChildHandler(int sig);
void AcceptConnections(int server_socket);

int main() 
{
    
    /* Set up vars for accepting connections from GDB */
    int server_socket;
    struct sockaddr_in server_address;

    /* Set up signal handling for parent and child */
    signal(SIGUSR1, ChildHandler);
    signal(SIGUSR2, ParentHandler);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) 
    {
        perror("socket");
        exit(1);
    }
    /* Set up socket for accepting connections from GDB */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(1234);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) 
    {
        perror("bind");
        exit(1);
    }

    if (listen(server_socket, 1) < 0) 
    {
        perror("listen");
        exit(1);
    }

    /* Accept connections from GDB */
    AcceptConnections(server_socket);

    /* Loop forever */
    while (1) {
        pause(); /* Wait for signal */
    }
    return 0;
}

void ParentHandler(int sig) 
{
    /* Parent signal handler (empty) */
    return;
}

void ChildHandler(int sig) 
{
    printf("Child received SIGUSR1\n");
    sleep(1); /* Wait a second */
    printf("Child sending SIGUSR2\n");
    kill(getppid(), SIGUSR2); /* Send signal to parent */
}

void AcceptConnections(int server_socket) 
{
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket < 0) 
    {
        perror("accept");
        exit(1);
    }

    /* Redirect stdin, stdout, and stderr to socket */
    dup2(client_socket, STDIN_FILENO);
    dup2(client_socket, STDOUT_FILENO);
    dup2(client_socket, STDERR_FILENO);
}

