// Client Side program to test
// the TCP server that returns
// message in a file

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// PORT number
#define PORT 8080

int main()
{
    // Socket id
    int clientSocket, ret,s;
    FILE *fp;
    // Client socket structure
    struct sockaddr_in cliAddr;

    struct sockaddr_in serverAddr;

    // char array to store incoming message
    char buffer[1024],name[100],fname[100],rcvg[100];

    // Creating socket id
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Client Socket is created.\n");

    // Initializing socket structure with NULL
    memset(&cliAddr, '\0', sizeof(cliAddr));

    // Initializing buffer array with NULL
    memset(buffer, '\0', sizeof(buffer));

    // Assigning port number and IP address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    // 127.0.0.1 is Loopback IP
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect() to connect to the server
    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    if (ret < 0) {
        printf("Error in connection.\n");
        exit(1);
    }

    printf("Connected to Server.\n");

    while (1) {
        printf("Enter the existing file name\t");
        scanf("%s",name);
        printf("Enter the new file name\t");
        scanf("%s",fname);
        fp=fopen(fname,"w");
        while(1) {
            send(clientSocket,name,sizeof(name),0);
            s=recv(clientSocket,rcvg,100,0);
            if(s<0)
                printf("Error in receiving data");
            else {
                rcvg[s]='\0';
                if(strcmp(rcvg,"error")==0) {
                    printf("File is not available\n");
                }
                if(strcmp(rcvg,"completed")==0) {
                    printf("File is transferred........\n");
                    break;
                    fclose(fp);
                    close(clientSocket);
                } else {
                    // Printing the message on screen
                    fputs(rcvg,stdout);
                    fprintf(fp,"%s",rcvg);
                    bzero(rcvg,sizeof(rcvg));
                }
            }
    }
    return 0;
    }
}
