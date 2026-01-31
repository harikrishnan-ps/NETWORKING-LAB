#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
 
int main() {
    int sock_desc, f, n, i = 0, k = 0, send_count;
    int front = 0, rear = 0;
    char buffer[30][100], queue[30][100];
    char client_message[100], server_message[100];
    struct sockaddr_in server_addr;
 
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    connect(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
 
    printf("Enter window size: ");
    scanf("%d", &f);
    printf("Enter total number of packets: ");
    scanf("%d", &n);
    printf("Enter packets:\n");
    for (int x = 0; x < n; x++) scanf("%s", buffer[x]);
 
    for (int x = 0; x < f && x < n; x++) strcpy(queue[rear++], buffer[k++]);
 
    while (i < n) {
        if (i + f < n)
            send_count = f;
        else
            send_count = n - i;
 
        send(sock_desc, &send_count, sizeof(send_count), 0);
 
        for (int x = 0; x < send_count; x++) {
            strcpy(client_message, queue[front + x]);
            send(sock_desc, client_message, sizeof(client_message), 0);
        }
 
        for (int x = 0; x < send_count; x++) {
            recv(sock_desc, server_message, sizeof(server_message), 0);
            if (!strcmp(server_message, "y") || !strcmp(server_message, "Y")) {
                printf("Acknowledged: %s\n", queue[front]);
                i++;
                front++;
                if (k < n) strcpy(queue[rear++], buffer[k++]);
            } 
            else {
                printf("Not Acknowledged: %s\n", queue[front]);
                strcpy(queue[rear++], queue[front]);
                front++;
            }
        }
    }
 
    send_count = -1;
    send(sock_desc, &send_count, sizeof(send_count), 0);
    close(sock_desc);
    return 0;
}