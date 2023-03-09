#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 1234
#define MIN_PINGS 3
#define MAX_PINGS 10
#define MIN_WAIT 3
#define MAX_WAIT 10
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    int i = 0;
    int num_bytes = 0;
    int num_pings = 0;
    int wait_time = 0;
    srand(time(NULL));
    
    wait_time = rand() % (MAX_WAIT - MIN_WAIT + 1) + MIN_WAIT;;
    num_pings = rand() % (MAX_PINGS - MIN_PINGS + 1) + MIN_PINGS;
    

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server_address.sin_port = htons(SERVER_PORT);

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) 
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }


    printf("Sending %d pings...\n", num_pings);

    for ( i= 1; i <= num_pings; i++) 
    {
        printf("Sending %d pings...\n", num_pings);
        printf("Sending ping %d...\n", i);
        send(client_socket, "ping", strlen("ping"), 0);

        printf("Waiting %d seconds...\n", wait_time);
        sleep(wait_time);

     	num_bytes = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (num_bytes <= 0) 
        {
            if (num_bytes == 0) 
            {
                printf("Server disconnected\n");
            } else {
                perror("TCP recv failed");
            }

            break;
        } 
        else 
        {
            buffer[num_bytes] = '\0';
            printf("Received %s\n", buffer);
        }
    }

    printf("Disconnecting from server...\n");
    close(client_socket);

    return 0;
}

