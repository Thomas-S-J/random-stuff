#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main(int argc, char *argv[]){

    //creates a socket
    int mysocket = socket(AF_INET, SOCK_STREAM, 0);

    //specify an address for socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(mysocket, (struct sockaddr *) &server_address, sizeof(server_address));
    //check for error with connection
    if(connection_status == -1){
        printf("There was an error making a connection to the remote socket\n");
    }

    //recieve data from the server
    char server_response[256];
    recv(mysocket, &server_response, sizeof(server_response), 0);
    printf("The server sent the data: %s\n", server_response);
    close(mysocket);
    return 0;
}
