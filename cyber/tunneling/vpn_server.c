#include <sys/select.h> /*fd_set select FD_***/
#include <unistd.h> /*fcntl write*/
#include <assert.h> /**/
#include <stdio.h> /*sscanf*/
#include <fcntl.h> /*fcntl*/
#include <sys/time.h> /*timeval*/
#include <string.h> /*memset strcmp*/
#include <sys/types.h> /* */
#include <sys/socket.h> /* listen */



#include "interface.h"
#include "vpn_server.h"
#include "tcp.h"
#include "stdin.h"

#define PORT 4443
#define SERVER_ADDR "10.20.0.1/16"
#define MTU 1500
#define BUFFER_SIZE 1024
#define MAX_CONCUR_TCP 1
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define SHTDWN_MSG "Server shutdown\n"
#define UKWN_CMD "Unknown command\n"

int main()
{
	fd_set rfds;
	char buffer[MTU];
	char msg[BUFFER_SIZE];
	int client_sockets[MAX_CONCUR_TCP];
	int tcpfd = 0;
	int tunfd = 0;
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
	
	if(-1 == listen(tcpfd, SOMAXCONN))
	{
		close(tcpfd);
	}
	
	tunfd = InterfaceCreate();
	
	if(tunfd < 0)
	{
		close(tcpfd);
		return tunfd;
	}
	
	if(fcntl(tunfd, F_SETFL, O_NONBLOCK) < 0)
	{
		CloseFds(tcpfd, tunfd);
		return 1;
	}
	
	retval = InterfaceSet(SERVER_ADDR, MTU);
	
	if(0 != retval)
	{
		CloseFds(tcpfd, tunfd);
		return retval;
	}
	
	for(; i < MAX_CONCUR_TCP; ++i)
	{
		client_sockets[i] = 0;
	}
	
	while(1)
	{
		/*set FDs in select set*/
		FD_ZERO(&rfds);
		FD_SET(tcpfd, &rfds);
		FD_SET(tunfd, &rfds);
		FD_SET(STDIN_FILENO, &rfds);
		
		/*calc max fd entry point*/
		maxfd = MAX2(tunfd, tcpfd);
		
		for(i=0; i < MAX_CONCUR_TCP; ++i)
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
		
		status = select(maxfd + 1, &rfds, NULL, NULL, NULL);
		
		/*we got read movement in rfds*/
		if(status > 0)
		{
			/*stdin read movement*/
			if(FD_ISSET(STDIN_FILENO, &rfds))
			{
				if(-1 == StdinRecieve(buffer, sizeof(buffer)))
				{
					CloseFds(tcpfd, tunfd);
					return 1;
				}
				
				if(EOF == ParseMessage(buffer, msg))
				{
					CloseFds(tcpfd, tunfd);
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
					CloseFds(tcpfd, tunfd);
					return 0;
				}
				
			}
			
			/*tcp handshake request*/
			if(FD_ISSET(tcpfd, &rfds))
			{
				newsockfd = TcpAccept(tcpfd, PORT);
				if(-1 == newsockfd)
				{
					CloseFds(tcpfd, tunfd);
				}
				
				for(i=0; i < MAX_CONCUR_TCP; ++i)
				{
					if(0 == client_sockets[i])
					{
						client_sockets[i] = newsockfd;
						break;
					}
				}
			}
			/*tcp client read movement*/
			for(i=0; i < MAX_CONCUR_TCP; ++i)
			{
				if(FD_ISSET(client_sockets[i], &rfds))
				{
					retval = TcpRecieve(client_sockets[i], buffer, sizeof(buffer));
					if(-1 == retval)
					{
						CloseFds(tcpfd, tunfd);
						return -1;
					}
					
					else if(0 == retval)
					{	
						client_sockets[i] = 0;
						continue;
					}
					
					if(EOF == ParseMessage(buffer, msg))
					{
						CloseFds(tcpfd, tunfd);
						return 1;
					}
						
				}
			}
			
			/* TUN read movement */
			if(FD_ISSET(tunfd, &rfds))
			{
				retval = InterfaceRecieve(tunfd, buffer, sizeof(buffer));
				if(0 > retval)
				{
					CloseFds(tcpfd, tunfd);
					return -1;
				}
				
				continue;
				if(-1 == TcpRespond(tcpfd, msg, sizeof(msg)))
				{
					CloseFds(tcpfd, tunfd);
					return 1;
				}
			}
			
			
		}
		/*select failed*/
		else
		{
			CloseFds(tcpfd, tunfd);
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
int CloseFds(int frst_fd, int scnd_fd)
{
	int retval = 0;
	
	retval = close(frst_fd);
	if(-1 == retval)
	{ 
		close(scnd_fd);
		return retval;
	}
	retval = close(scnd_fd);
	return retval;
}


