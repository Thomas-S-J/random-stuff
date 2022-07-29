// Server side program that accepts connection from
// every client concurrently

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

// PORT number
#define PORT 8080

int main()
{
    // Server socket id
    int sockfd, ret,n;
    char rcv[100],fileread[100];
    // Server socket address structures

    FILE *fp;
    struct sockaddr_in serverAddr;

    // Client socket id
    int clientSocket;

    // Client socket address structures
    struct sockaddr_in cliAddr;

    // Stores byte size of server socket address
    socklen_t addr_size;

    // Child process id
    pid_t childpid;

    // Creates a TCP socket id from IPV4 family
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Error handling if socket id is not valid
    if (sockfd < 0) {
        printf("Error in connection.\n");
        exit(1);
    }

    printf("Server Socket is created.\n");

    // Initializing address structure with NULL
    memset(&serverAddr, '\0', sizeof(serverAddr));

    // Assign port number and IP address
    // to the socket created
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    // 127.0.0.1 is a loopback address
    serverAddr.sin_addr.s_addr
        = inet_addr("127.0.0.1");

    // Binding the socket id with
    // the socket structure
    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Error handling
    if (ret < 0) {
        printf("Error in binding.\n");
        exit(1);
    }

    // Listening for connections (upto 10)
    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n\n");
    }

    int cnt = 0;
    while (1) {

        // Accept clients and
        // store their information in cliAddr
        clientSocket = accept(sockfd, (struct sockaddr*)&cliAddr, &addr_size);

        // Error handling
        if (clientSocket < 0) {
            exit(1);
        }

        // Displaying information of
        // connected client
        printf("Connection accepted from %s:%d\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

        // Print number of clients
        // connected till now
        printf("Clients connected: %d\n\n", ++cnt);


        // Creates a child process
        if ((childpid = fork()) == 0) {
            n = recv(clientSocket, rcv, 100, 0);
            rcv[n] ='\0';
            fp = fopen(rcv, "r");
            if(fp == NULL){
                send(clientSocket, "error", 5, 0);
                close(clientSocket);
            }else{
                while(fgets(fileread, sizeof(fileread), fp)){
                    if(send(clientSocket, fileread, sizeof(fileread), 0)<0){
                        printf("Can’t send file contents\n");
                    }
                    sleep(1);
                }
                if(!fgets(fileread,sizeof(fileread),fp)){
                    //when file pointer reaches end of file, file transfer “completed” message is send to accepted client connection using newsd, socket file descriptor.
                    send(clientSocket,"completed", 9, 0);
                }
            }
            // Closing the server socket id
            close(sockfd);
        }
    }

    // Close the client socket id
    close(clientSocket);
    return 0;
}
