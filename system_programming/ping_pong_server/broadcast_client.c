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
    int broadcast_enable = 1;
    int retval = 0;
    socklen_t len = 0;

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) 
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
	
	retval = setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable));
	if(-1 == retval)
	{
		return 1;
	}
	
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server_address.sin_port = htons(SERVER_PORT);

    for ( i= 1; i <= num_pings; i++) 
    {
        printf("Sending %d pings...\n", num_pings);
        printf("Sending ping %d...\n", i);
        sendto(client_socket, "ping\n", strlen("ping\n"), 0, (const struct sockaddr*)&server_address, sizeof(server_address));

        printf("Waiting %d seconds...\n", wait_time);
        sleep(wait_time);

    	num_bytes = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_address, &len);
        if (num_bytes < 0) 
        {
			perror("UDP recv failed");
			break;
        } 
        else 
        {
            buffer[num_bytes] = '\0';
            printf("Received %s\n", buffer);
        }
    }

    close(client_socket);

    return 0;
}

