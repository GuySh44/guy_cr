#include <sys/socket.h> /*socket */
#include <arpa/inet.h> /*htonl htons*/
#include <netinet/in.h>  /*sockaddr_in*/
#include <stddef.h> /**/
#include <sys/types.h> /*bind recvfrom sendto*/
#include <assert.h> /**/
#include <string.h> /*strcmp*/

/*
Reviewer: raz
*/



int UdpOpenSocket(int port)
{
	int host_addrlen = 0;
	int sockfd = 0;
    struct sockaddr_in host_addr;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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


int UdpHandle(int sockfd, char *buf, size_t len, int port, const char *msg)
{
    struct sockaddr_in client_addr;
	socklen_t client_addrlen = 0;
	int retval = 0;
	
	assert(buf);
	
	client_addrlen = sizeof(client_addr);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	retval = recvfrom(sockfd, buf, len, MSG_DONTWAIT, (struct sockaddr*)&client_addr, &client_addrlen);
	
	if(-1 == retval)
	{
		return retval;
	}
	
	retval = -2;
	
	if(0 == strcmp("ping\n", buf))
	{
		retval = sendto(sockfd, msg, strlen((char*)msg), MSG_DONTWAIT, (struct sockaddr*)&client_addr, client_addrlen);
	}
	
	return retval;
}


