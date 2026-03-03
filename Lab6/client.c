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

    struct sockaddr_in serv_addr;
    char buffer[128] = {0};

    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("socket");
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORTNUM);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(client_socket);
        return 1;
    }

    // Connect
    if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(client_socket);
        return 1;
    }

    // Send "hello"
    const char *hello = "hello";
    if (send(client_socket, hello, strlen(hello), 0) < 0) {
        perror("send hello");
    }

    // Read "Hello Back"
    ssize_t n = read(client_socket, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("read");
        close(client_socket);
        return 1;
    }
    buffer[n] = '\0';
    printf("Client Received: %s\n", buffer);

    // Read array from user
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter %d numbers:\n", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    // Send size first
    send(client_socket, &size, sizeof(int), 0);

    // Send array
    send(client_socket, arr, size * sizeof(int), 0);

    // Receive sum
    int sum;
    if (read(client_socket, &sum, sizeof(int)) < 0) {
        perror("read sum");
        close(client_socket);
        return 1;
    }

    printf("Client received Sum = %d\n", sum);

    close(client_socket);
    return 0;
}