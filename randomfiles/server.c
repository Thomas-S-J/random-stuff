#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>

int main(int argc, char *argv[]){

    char server_message[256] = "You have recieved the server";
    //create the socket
    int mysocket = socket(AF_INET, SOCK_STREAM, 0);

    //define the address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bind the socket to our specified IP and port
    bind(mysocket, (struct sockaddr*)&server_address, sizeof(server_address));

    listen(mysocket, 3);
    int client_socket = accept(mysocket, NULL, NULL);
    send(client_socket, server_message, sizeof(server_message), 0);
    close(mysocket);
    return 0;
}
