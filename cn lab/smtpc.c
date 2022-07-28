#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char* argv[])
{
     struct sockaddr_in server, client;
     char str[50]= "hi";
     char mail_f[50],mail_to[50],msg[20],c;
     int t = 0;
     socklen_t l = sizeof(server);

     int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

     server.sin_family = AF_INET;
     server.sin_port = htons(8080);
     server.sin_addr.s_addr = inet_addr("127.0.0.1");
     client.sin_family = AF_INET;
     client.sin_port = htons(8080);
     client.sin_addr.s_addr = inet_addr("127.0.0.1");

     /* Step 1: Attempt to establish a connection with the SMTP server.
                The SMTP server will respond back with 220
      *
     */
     printf("Sending HI to server");
     sleep(10);
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr*)&server,sizeof(server))<0)
        printf("Error in sento");
     if(recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,&l)<0)
        printf("Error in recv");
     printf("\nGreeting msg is %s",str);
     if(strncmp(str,"220",3))
     printf("\nConn not established \n code 220 expected");

     /* Step 2: Send a HELO message to SMTP server.
      *         The server should respond back with 250 OK or simply 250
      */
     printf("\nSending HELO");
     strcpy(str,"HELO");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,sizeof(server))<0)
        printf("Error in sendto");
     sleep(3);
     printf("\nReceiving from server");
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,&l))<0)
        printf("Error in recv");
     if(strncmp(str,"250",3))
        printf("\nOK not received from server");
     printf("\nServer has send %s",str);

     /* Step 3: Send a MAIL FROM message to SMTP server.
      *         The server should respond back with a 250 OK or simply 250
      *
      */
     printf("\nEnter FROM address\n");
     scanf("%s",mail_f);
     strcpy(str,"MAIL FROM");
     strcat(str,mail_f);
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,sizeof(server))<0)
        printf("Error in sendto");
     sleep(3);
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,&l))<0)
        printf("Error in recv");
     if(strncmp(str,"250",3))
        printf("\nOK not received from server");
     printf("%s",str);

     /*
      * Step 4: Send a RCPT TO message to SMTP server.
      *         The server should respond back with a 250 OK or simply 250
      */
     printf("Enter TO address\n");
     scanf("%s",mail_to);
     strcpy(str,"RCPT TO");
     strcat(str,mail_to);
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,sizeof(server))<0)
        printf("Error in sendto");
     sleep(3);
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,&l))<0)
        printf("Error in recv");
     if(strncmp(str,"250",3))
        printf("\nOk not received from server");
     printf("%s",str);

     /*
      * Step 5: Send a DATA message to the SMTP server.
      *         The server should respond back with a 354 back to the client
      */
     printf("\nSending DATA to server");
     strcpy(str,"DATA");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,sizeof(server))<0)
        printf("Error in sendto");
     sleep(3);
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,&l))<0)
        printf("Error in recv");
     if(strncmp(str,"354",3))
        printf("\nOK not received from server");
     printf("%s",str);

     /*
      * Step 6: Send the email body to the SMTP server.
     */
     printf("\nEnter mail body");
     while(1)
     {
          c=getchar();
          if(c=='$')
          {
               msg[t]='\0';
               break;
          }
          if(c=='\0')
          continue;
          msg[t++]=c;
     }
     if(sendto(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&server,sizeof(server))<0)
     printf("Error in sendto");
     sleep(3);

     /*
      * Step 7: Send the QUIT message to close the connection.
      *         The server will respond back with a 221 message.
     */
     printf("\nSending QUIT to server");
     strcpy(str,"QUIT");
     if(sendto(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,sizeof(server))<0)
        printf("Error in sendto");
     if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr *)&server,&l))<0)
        printf("Error in recv");
     if(strncmp(str,"221",3))
        printf("\nOk not received from server");
     printf("\nServer has send GOODBYE.....Closing conn\n");
     printf("\n Bye");
     close(sockfd);
     return 0;
}
