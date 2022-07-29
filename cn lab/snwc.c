#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
void stop_and_wait(int client_socket){
    char frame[100];
    int seqNo = 0;
    char ack[6];
    int i=0;
    int next = 1;
    char exit[4] = {'e', 'x', 'i' ,'t'};

    while(1){
   	 int noExit = 0;
   	 if(next==1){
   		 bzero(frame,100);
   		 i=1;
   		 printf("\nEnter message to server : ");


   		 while((frame[i++]=getchar())!='\n');
   		 frame[i-1]='\0';

   		 frame[0] = seqNo;

   	 }

   	 sleep(1.5);
   	 send(client_socket,frame,sizeof(frame),0); //Send frame

   	 bzero(ack,6);  //Empty ack

   	 recv(client_socket,ack,sizeof(ack),0); //Receive ack
   	 if(ack[0]=='A'){

   		 //If frame acknowledged by server, proceed to next frame by setting next=1

   		 printf("Acknowledgement received from server for frame %d - [",seqNo);
   		 for(int j=1;frame[j]!='\0';j++) printf("%c",frame[j]);
   		 printf("]\n");
   		 seqNo = seqNo==0?1:0;
   		 next = 1;

   	 }
   	 else{
   		 //If frame not acknowledged, resend same frame by setting next =0
   		 next = 0;
   		 printf("Negative acknowledgement received from server for frame %d - [",seqNo);
   		 for(int j=1;frame[j]!='\0';j++) printf("%c",frame[j]);
   		 printf("]\nResending frame %d - [",seqNo);
   		 for(int j=1;frame[j]!='\0';j++) printf("%c",frame[j]);
   		 printf("]\n");

   	 }

   	 //If frame contains the message "exit", exit the network
   	 for(int j=1;j<5;j++){
   		 if(frame[j]!=exit[j-1]) {
   			 noExit = 1;
   			 break;
   		 }
   	 }
   	 if(noExit==0){
   		 printf("Client has successfully exited the network ... \n");
   		 return;
   	 }




    }

}

