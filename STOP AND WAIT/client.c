#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
 
void main(){
int sock_desc;
struct sockaddr_in server_addr;
char server_message[100],client_message[100],packet[100][100];
int n,i;
 
sock_desc = socket(AF_INET, SOCK_STREAM, 0);
 
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(2000);
   server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
   connect(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
   printf("Enter number of packets: ");
   scanf("%d",&n);
   printf("enter packets:");
   for(i=0;i<n;i++){
   scanf("%s",packet[i]);
   }
   i=0;
while(i<n){
strcpy(client_message,packet[i]);
    send(sock_desc, client_message, strlen(client_message), 0);
    recv(sock_desc, server_message, sizeof(server_message), 0);
if(!strcmp(server_message,"y")){
i++;
printf("Acknowledged %s\n", client_message);    
}
else{
printf("Not Acknowledged %s\nResending..\n", client_message);
}
}
   close(sock_desc);
}