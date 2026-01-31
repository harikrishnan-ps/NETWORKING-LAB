#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
 
int main(){
    int sock_desc, client_sock;
    struct sockaddr_in server_addr, client_addr;
    char server_message[100], client_message[100];
    char buffer[100][100];
    int f, i;
 
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 
    bind(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(sock_desc, 5);
 
    socklen_t client_len = sizeof(client_addr);
    client_sock = accept(sock_desc, (struct sockaddr*)&client_addr, &client_len);
 
    while(1){
        recv(client_sock, &f, sizeof(f), 0);
        if(f==-1){break;}
        printf("Frames Received:");
        for(i = 0; i < f; i++){
            recv(client_sock, buffer[i], sizeof(buffer[i]), 0);
            printf(" %s", buffer[i]);
        }
 
        for(i = 0; i < f; i++){
            printf("\nFrame %s Ack? (y/n): ", buffer[i]);
            scanf("%s", server_message);
            send(client_sock, server_message, sizeof(server_message), 0);
        }
    }
 
    close(client_sock);
    close(sock_desc);
    return 0;
}