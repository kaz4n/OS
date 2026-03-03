#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 7777

int main() {

    int server_socket,client_socket;
    struct sockaddr_in serv_addr;
    int addrlen = sizeof(serv_addr);
    char buffer[128] = {0};

    //  Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Bind socket
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORTNUM);

    bind(server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Listen
    listen(server_socket, 3);

    printf("Listening to client...\n");

    // Accept connection
client_socket = accept(server_socket, (struct sockaddr *)&serv_addr, (socklen_t*)&addrlen);

    // Read "hello"
    read(client_socket, buffer, 128);
    printf("Server Received: %s\n", buffer);

    // Send "Hello back"
    char *reply = "Hello back";
    send(client_socket, reply, strlen(reply), 0);

    // Receive array size
    int size;
    read(client_socket, &size, sizeof(int));

    printf("Waiting for client to send an array...");
    // Receive array
    int arr[100];
    int sizeOfArray = read(client_socket, arr, size * sizeof(int));
    int numOfItems = sizeOfArray/sizeof(int);
    printf("Number of bytes read = %d;  thus %d is the size of the array\n", sizeOfArray, numOfItems);

    printf("Array received:\n");

    int sum = 0;
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        sum += arr[i];
    }

    printf("\nFinished Reading\nComputing Sum:\nSum = %d\n", sum);

    // Send sum back
    send(client_socket, &sum, sizeof(int), 0);

    close(client_socket);
    close(server_socket);

    return 0;
}