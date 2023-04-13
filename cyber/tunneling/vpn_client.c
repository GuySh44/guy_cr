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

#define GATEWAY "192.168.56.254"
#define PORT 4443
#define CLIENT_ADDR "10.20.0.2/16"
#define SERVER_ADDR "192.168.6.11"
#define VPN_SERVER_ADDR "10.20.0.1"
#define MTU 1400
#define BUFFER_SIZE 1024
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define SHTDWN_MSG "Vpn client shutdown\n"
#define UKWN_CMD "Unknown command\n"

int main()
{
	fd_set rfds;
	char buffer[BUFFER_SIZE];
	char msg[BUFFER_SIZE];
	int csockfd = 0;
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
	
	tunfd = InterfaceCreate();
	
	if(tunfd < 0)
	{
		return tunfd;
	}
	
	if(fcntl(tunfd, F_SETFL, O_NONBLOCK) < 0)
	{
		CloseFds(csockfd, tunfd);
		return 1;
	}
	
	retval = InterfaceSet(VPN_SERVER_ADDR, MTU);
	
	if(0 != retval)
	{
		CloseFds(csockfd, tunfd);
		return retval;
	}
	
	retval = InterfaceSetClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
	
	if(0 != retval)
	{
		InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
		CloseFds(csockfd, tunfd);
		return retval;
	}
	
	csockfd = TcpConnectClient(SERVER_ADDR, PORT);
	if(csockfd < 0)
	{
		InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
		CloseFds(csockfd, tunfd);
		return csockfd;
	}
	
	
	while(1)
	{
		/*set FDs in select set*/
		FD_ZERO(&rfds);
		FD_SET(csockfd, &rfds);
		FD_SET(tunfd, &rfds);
		FD_SET(STDIN_FILENO, &rfds);
		
		/*calc max fd entry point*/
		maxfd = MAX2(tunfd, csockfd);
		
		
		status = select(maxfd + 1, &rfds, NULL, NULL, NULL);
		
		/*we got read movement in rfds*/
		if(status > 0)
		{
			/*stdin read movement*/
			if(FD_ISSET(STDIN_FILENO, &rfds))
			{
				if(-1 == StdinRecieve(buffer, sizeof(buffer)))
				{
					InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
					CloseFds(csockfd, tunfd);
					return 1;
				}
				
				retval = StdResponse(buffer);
				if(0 == retval)
				{
					write(STDOUT_FILENO, UKWN_CMD, strlen(UKWN_CMD));
					continue;
				}
				
				if(1 == retval)
				{
					write(STDOUT_FILENO, SHTDWN_MSG, strlen(SHTDWN_MSG));
					InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
					CloseFds(csockfd, tunfd);
					return 0;
				}
				
			}
			/*tcp client read movement*/
			if(FD_ISSET(csockfd, &rfds))
			{
				retval = TcpRecieve(csockfd, buffer, sizeof(buffer));
				if(-1 == retval)
				{
					InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
					CloseFds(csockfd, tunfd);
					return -1;
				}
				
				else if(0 == retval)
				{	
					csockfd = 0;
					continue;
				}
				
				if(-1 == InterfaceRespond(tunfd, buffer, sizeof(buffer)))
				{
					InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
					CloseFds(csockfd, tunfd);
					return 1;
				}	
			}
			
			/* TUN read movement */
			if(FD_ISSET(tunfd, &rfds))
			{
				retval = InterfaceRecieve(tunfd, buffer, sizeof(buffer));
				if(-1 == retval)
				{
					InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
					CloseFds(csockfd, tunfd);
					return -1;
				}
				
				else if(0 == retval)
				{	
					csockfd = 0;
					continue;
				}
				
				
				if(-1 == TcpRespond(csockfd, buffer, sizeof(buffer)))
				{
					InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
					CloseFds(csockfd, tunfd);
					return 1;
				}
			}
			
			
		}
		/*select failed*/
		else
		{
			InterfaceCleanClientTable(VPN_SERVER_ADDR, SERVER_ADDR, GATEWAY);
			CloseFds(csockfd, tunfd);
			return 1;
		}
		
	}
	
	return 0;
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



