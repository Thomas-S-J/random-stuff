#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
     char str[50], msg[100];

     int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

     struct sockaddr_in server, client;
     server.sin_family = AF_INET;
     server.sin_port = htons(8080);
     server.sin_addr.s_addr = inet_addr("127.0.0.1");

     bind(sockfd, (struct sockaddr*)&server, sizeof(server));

     socklen_t client_len = sizeof(client);
     printf("Server waiting......\n");
     sleep(3);

     // Step 1: Accept TCP connection from client and accept it by returning the code 220
     if(recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, &client_len)<0)
        printf("Error in recvfrom()!\n");
     printf("TCP connection attempt from client: %s\n",str);
     printf("Sending response to client\n");
     strcpy(str,"220 : 127.0.0.1");
     sleep(10);
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,sizeof(client))<0)
        printf("Error in send");
     sleep(3);

     // Step 2: Receive the HELO message from the SMTP client. Respond back with 250 OK
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,&client_len)),0)
        printf("Error in recv");
     if(strncmp(str,"HELO",4))
        printf("HELO expected from client....");
     printf("\n%s",str);
     printf("\nSending response...");
     strcpy(str,"250 OK");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,sizeof(client))<0)
        printf("Error in send");
     sleep(3);

     //Step 3: Receive the MAIL FROM message from the SMTP client. Respond back with 250 OK
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,&client_len))<0)
        printf("Error in recv");
     if(strncmp(str,"MAIL FROM",9))
        printf("MAIL FROM expected from client...");
     printf("\n%s",str);
     printf("\nSending response....");
     strcpy(str,"250 OK");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,sizeof(client))<0)
        printf("Error in send");
     sleep(3);

     // Step 4: Receive the RCPT TO message from the SMTP client. Respond back with a 250 OK
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,&client_len))<0)
        printf("Error in recv");
     if(strncmp(str,"RCPT TO",7))
        printf("\nRCPT TO expected from client....");
     printf("\n%s",str);
     printf("\nSending response....");
     strcpy(str,"250 OK");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,sizeof(client))<0)
        printf("Error in send");
     sleep(3);

     // Step 5: Receive the DATA message from the SMTP client. Respond back with 354
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,&client_len))<0)
        printf("Error in recv");
     if(strncmp(str,"DATA",4))
        printf("\nDATA expected from client....");
     printf("\n%s",str);
     printf("\nSending response....");
     strcpy(str,"354 Go ahead");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,sizeof(client))<0)
        printf("Error in send");

     // Step 6: Receive the mail body. Display it on the screen.
     if((recvfrom(sockfd,msg,sizeof(str),0,(struct sockaddr *)&client,&client_len))<0)
        printf("Error in recv");
     printf("mail body received\n");
     printf("%s\n",msg);

     // Step 7: Receive the QUIT message from the SMTP client. Respond back with 221
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,&client_len))<0)
     printf("Error in recv");
     if(strncmp(str,"QUIT",4))
        printf("QUIT expected from client....");
     printf("\nSending quit...");
     strcpy(str,"221 OK");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&client,sizeof(client))<0)
     printf("Error in send");

     close(sockfd);
     return 1;
}
