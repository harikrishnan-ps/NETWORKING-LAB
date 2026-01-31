#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
 
void main(){
int sock_desc,client_sock;
struct sockaddr_in server_addr,client_addr;
char server_message[100],client_message[100];
sock_desc = socket(AF_INET, SOCK_STREAM, 0);
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr =htonl( INADDR_ANY);
 
    bind(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(sock_desc, 5);
 
    socklen_t client_len = sizeof(client_addr);
    client_sock = accept(sock_desc, (struct sockaddr*)&client_addr, &client_len);
 
while(1){ 
    recv(client_sock, client_message, sizeof(client_message), 0);
    printf("Client says: %s\n", client_message);
puts("Ack?(Y|N)");
scanf("%s",server_message);
    send(client_sock, server_message, strlen(server_message), 0);
 }
    close(client_sock);
    close(sock_desc);
}