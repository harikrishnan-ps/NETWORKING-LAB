#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
 
int main(){
    int sock_desc;
    struct sockaddr_in server_addr;
    char server_message[100], client_message[100], packet[100][100];
    int n, i, f, index, send_count;
 
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    connect(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
 
    printf("Enter number of packets: ");
    scanf("%d", &n);
    printf("Enter window size: ");
    scanf("%d", &f);
 
    printf("Enter packets: ");
    for(i = 0; i < n; i++){
        scanf("%s", packet[i]);
    }
 
    i = 0;
    while(i < n){
    if(i + f < n) {
    send_count = f;
}
else{
    send_count = n - i;
}
 
      send(sock_desc, &send_count, sizeof(send_count), 0);
 
      for(index = 0; index < send_count; index++){
           strcpy(client_message, packet[i + index]);
           send(sock_desc, client_message, sizeof(client_message), 0);
      }
 
      for(index = 0; index < send_count; index++){
           recv(sock_desc, server_message, sizeof(server_message), 0);
           if(strcmp(server_message, "y") == 0){
               printf("Acknowledged %s\n", packet[i]);
               i++;
           } else {
               printf("Not Acknowledged %s\nResending window...\n", packet[i]);
               break;
           }
       }
    }
    send_count=-1;
    send(sock_desc, &send_count, sizeof(send_count), 0);
    close(sock_desc);
    return 0;
}