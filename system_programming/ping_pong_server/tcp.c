#include <sys/socket.h> 
#include <arpa/inet.h> /*htonl htons*/
#include <netinet/in.h> 
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int TcpOpenSocket(int port)
{
	int host_addrlen = 0;
	int sockfd = 0;
    struct sockaddr_in host_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		return -1;
	}
	
	host_addrlen = sizeof(host_addr);
	
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (0 != bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen)) 
    {
    	return -2;
	}
	
	return sockfd;
}

int TcpRespond(int clientfd, void *msg, size_t msg_len)
{
	return send(clientfd, msg, msg_len, MSG_DONTWAIT);
}


int TcpConnect(int tcpfd, int port)
{
	int newsockfd = 0;
	int host_addrlen = 0;
    struct sockaddr_in host_addr;
	
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
	host_addrlen = sizeof(host_addr);
	newsockfd = accept(tcpfd, (struct sockaddr *)&host_addr,(socklen_t *)&host_addrlen);
	
	if(-1 == newsockfd)
	{
		return -1;
	}
	
	return newsockfd;
} 

int TcpDisconnect(int socketfd)
{
	if(-1 == close(socketfd))
	{
		return -1;
	}
	return 0;
}

int TcpRecieve(int sockfd, void *buf, size_t len)
{
	return recv(sockfd, buf, len, MSG_DONTWAIT);
}

