#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int queue[100];
int front = 0, rear = -1, size = 0;

void add_packet(int packet_size, int bucket_size) {
    if (size + packet_size > bucket_size) {
        printf("Packet of size %d dropped. Bucket overflow!\n", packet_size);
    } else {
        rear = (rear + 1) % 100; // Circular queue
        queue[rear] = packet_size;
        size += packet_size;
        printf("Packet of size %d added. Current bucket load: %d\n", packet_size, size);
    }
}

void leak(int output_rate) {
    while (size > 0) {
        printf("Leaking %d packets...\n", output_rate);
        int leaked = 0;
        while (leaked < output_rate && size > 0) {
            int packet_size = queue[front];
            front = (front + 1) % 100; // Circular queue
            size -= packet_size;
            leaked += packet_size;
            printf("Leaked packet of size %d\n", packet_size);
        }
        printf("Current bucket load after leak: %d\n", size);
        sleep(1);
    }
}

int main() {
    int bucket_size, output_rate, num_packets;
    printf("Enter the bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter the output rate: ");
    scanf("%d", &output_rate);
    printf("Enter the number of packets: ");
    scanf("%d", &num_packets);
    for (int i = 0; i < num_packets; i++) {
        int packet_size;
        printf("Enter size of packet %d: ", i + 1);
        scanf("%d", &packet_size);
        add_packet(packet_size, bucket_size);
    }
     // Simulate leaking packets
    printf("\nStarting to leak packets...\n");
    leak(output_rate);

    printf("All packets have been leaked. Bucket is empty.\n");

    return 0;
}