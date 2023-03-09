#include <sys/select.h> /*fd_set select FD_***/
#include <unistd.h> /*fcntl write*/
#include <assert.h> /**/
#include <stdio.h> /*sscanf*/
#include <fcntl.h> /*fcntl*/
#include <sys/time.h> /*timeval*/
#include <string.h> /*memset strcmp*/

/*
Reviewer: raz
*/

#include "logger.h"
#include "stdin.h"
#include "tcp.h"
#include "udp.h"
#include "integration.h"

#define PORT 1234
#define BUFFER_SIZE 1024
#define LOGGER_TIMEOUT 7
#define MAX_CONCUR_TCPCLIENT 10
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define PONG "pong\n"
#define SHTDWN_MSG "Server shutdown\n"
#define UKWN_CMD "Unknown command\n"

int main()
{
	fd_set rfds;
	struct timeval tv;
	char buffer[BUFFER_SIZE];
	char msg[BUFFER_SIZE];
	int client_sockets[MAX_CONCUR_TCPCLIENT];
	int tcpfd = 0;
	int udpfd = 0;
	int maxfd = 0;
	int status = 0;
	int retval = 0;
	int i = 0;
	int newsockfd = 0;
	
	memset(buffer, '\0', BUFFER_SIZE);
	memset(msg, '\0', BUFFER_SIZE);
	
	/*set stdin as non blocking*/
	if(fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK) < 0)
	{
		return 1;
	}
	
	/*set stdout as nonblocking*/
	if(fcntl(STDOUT_FILENO, F_SETFL, O_NONBLOCK) < 0)
	{
		return 1;
	}
	
	tcpfd = TcpOpenSocket(PORT);
	if(tcpfd < 0)
	{
		return tcpfd;
	}
	
	udpfd = UdpOpenSocket(PORT);
	if(udpfd < 0)
	{
		close(tcpfd);
		return udpfd;
	}
	
	if (-1 == listen(tcpfd, SOMAXCONN))
	{
		close(tcpfd);
		close(udpfd);
	}
	
	for(; i < MAX_CONCUR_TCPCLIENT; ++i)
	{
		client_sockets[i] = 0;
	}
	
	while(1)
	{
		/*timeout to 7 secs*/
		tv.tv_sec = LOGGER_TIMEOUT;
		tv.tv_usec = 0;
		/*set FDs in select set*/
		FD_ZERO(&rfds);
		FD_SET(STDIN_FILENO, &rfds);
		FD_SET(tcpfd, &rfds);
		FD_SET(udpfd, &rfds);
		
		/*calc max fd entry point*/
		maxfd = MAX2(udpfd, tcpfd);
		
		/*check for max fd, and add all open fds*/
		for(i=0; i < MAX_CONCUR_TCPCLIENT; ++i)
		{
			if(client_sockets[i] > maxfd)
			{
				maxfd = client_sockets[i];
			}
			
			if(client_sockets[i] > 0)
			{
				FD_SET(client_sockets[i], &rfds);
			}
		}
		
		status = select(maxfd + 1, &rfds, NULL, NULL, &tv);
		
		/*we got read movement in rfds*/
		if(status > 0)
		{
			/*stdin read movement*/
			if(FD_ISSET(STDIN_FILENO, &rfds))
			{
				if(-1 == StdinRecieve(buffer, sizeof(buffer)))
				{
					CloseFds(tcpfd, udpfd, client_sockets);
					return 1;
				}
				
				if(EOF == ParseMessage(buffer, msg))
				{
					CloseFds(tcpfd, udpfd, client_sockets);
					return 1;
				}
				
				retval = StdResponse(msg);
				if(0 == retval)
				{
					write(STDOUT_FILENO, UKWN_CMD, strlen(UKWN_CMD));
					continue;
				}
				
				if(1 == retval)
				{
					write(STDOUT_FILENO, SHTDWN_MSG, strlen(SHTDWN_MSG));
					CloseFds(tcpfd, udpfd, client_sockets);
					return 0;
				}
				
				if(2 == retval)
				{
					write(STDOUT_FILENO, PONG , strlen(PONG));
					continue;
				}
			}
			
			/*tcp handshake request*/
			if(FD_ISSET(tcpfd, &rfds))
			{
				newsockfd = TcpConnect(tcpfd, PORT);
				if(-1 == newsockfd)
				{
					CloseFds(tcpfd, udpfd, client_sockets);
				}
				
				for(i=0; i < MAX_CONCUR_TCPCLIENT; ++i)
				{
					if(0 == client_sockets[i])
					{
						client_sockets[i] = newsockfd;
						break;
					}
				}
			}
			
			/*tcp client read movement*/
			for(i=0; i < MAX_CONCUR_TCPCLIENT; ++i)
			{
				if(FD_ISSET(client_sockets[i], &rfds))
				{
					retval = TcpRecieve(client_sockets[i], buffer, sizeof(buffer));
					if(-1 == retval)
					{
						CloseFds(tcpfd, udpfd, client_sockets);
						return -1;
					}
					
					else if(0 == retval)
					{
						if(-1 == LogTcpClosed())
						{
							CloseFds(tcpfd, udpfd, client_sockets);
							return 1;
						}
						
						client_sockets[i] = 0;
						continue;
					}
					
					if(EOF == ParseMessage(buffer, msg))
					{
						CloseFds(tcpfd, udpfd, client_sockets);
						return 1;
					}
					
					if(0 == strcmp(msg, "ping"))
					{
						if(-1 == TcpRespond(client_sockets[i], PONG, sizeof(PONG)))
						{
							CloseFds(tcpfd, udpfd, client_sockets);
							return 1;
						}
					}	
				}
			}
			
			/*udp read movement*/
			if(FD_ISSET(udpfd, &rfds))
			{
				if(-1 == UdpHandle(udpfd, buffer, sizeof(buffer), PORT, PONG))
				{
					CloseFds(tcpfd, udpfd, client_sockets);
					return 1;
				}
				continue;
			}
		}
		/*timeout reached*/
		else if (0 == status)
		{
			if(-1 == LogTimeout())
			{
				CloseFds(tcpfd, udpfd, client_sockets);
				return 1;
			}
		}
		/*select failed*/
		else
		{
			CloseFds(tcpfd, udpfd, client_sockets);
			return 1;
		}
		
	}
	
	return 0;
}

/*redundant for now*/
int ParseMessage(char *buf, char *msg)
{
	assert(buf);
	assert(msg);
	
	
	return sscanf(buf, "%s", msg);
}

/*close fds incase of error/graceful exit*/
int CloseFds(int tcpfd, int udpfd, int *clients_fds)
{
	int i = 0;
	int retval = 0;
	
	assert(clients_fds);
	
	close(tcpfd);
	close(udpfd);
	
	for(; i < MAX_CONCUR_TCPCLIENT; ++i)
	{
		if(clients_fds[i] > 0)
		{
			retval = close(clients_fds[i]);
		}
	}
	return retval;
}

