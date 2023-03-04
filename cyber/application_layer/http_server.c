#include <arpa/inet.h> /*htonl*/
#include <errno.h> /*perror*/
#include <stdio.h> /*printf sscanf*/
#include <string.h> /*strlen*/
#include <sys/socket.h> /*sockaddr_in socket bind listen accept getsockname*/
#include <unistd.h> /*read write close*/

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html>Hello World</html>\r\n";

    int host_addrlen = 0;
    int client_addrlen = 0;
    struct sockaddr_in host_addr;
    struct sockaddr_in client_addr;
    
    /*create socket of IPV4 family, TCP datagram*/
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (-1 == sockfd) 
    {
        perror("webserver (socket)");
        return 1;
    }
    printf("socket created successfully\n");

    host_addrlen = sizeof(host_addr);

	/*IPV4*/
    host_addr.sin_family = AF_INET;
    /*Port 8000*/
    host_addr.sin_port = htons(PORT);
    /*accepts any host ip*/
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    client_addrlen = sizeof(client_addr);

	/*bind the socket to the address*/
    if (0 != bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen)) 
    {
        perror("webserver (bind)");
        return 1;
    }
    printf("socket successfully bound to address\n");

	/*server passive open listening*/
    if (0 != listen(sockfd, SOMAXCONN)) 
    {
        perror("webserver (listen)");
        return 1;
    }
    printf("server listening for connections\n");

	/*allow multiple connections*/
    while(1) 
    {

        int sockn = 0;
        int valread = 0;
        int valwrite = 0;
        char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
        /*block until connection requested*/
        int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr,
                               (socklen_t *)&host_addrlen);
        
        
        if (newsockfd < 0) 
        {
            perror("webserver (accept)");
            continue;
        }
        printf("connection accepted\n");

		/*get name of client*/
        sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr,
                                (socklen_t *)&client_addrlen);
        if (sockn < 0) 
        {
            perror("webserver (getsockname)");
            continue;
        }

		/*read request into buffer*/
        valread = read(newsockfd, buffer, BUFFER_SIZE);
        if (valread < 0) 
        {
            perror("webserver (read)");
            continue;
        }

		/*seperate request to specific parameters*/	
        sscanf(buffer, "%s %s %s", method, uri, version);
    	/*print the request internally*/
        printf("[%s:%u] %s %s %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), method, version, uri);

		/*write response to client*/
        valwrite = write(newsockfd, resp, strlen(resp));
        if (valwrite < 0) 
        {
            perror("webserver (write)");
            continue;
        }

        close(newsockfd);
    }

    return 0;
}
