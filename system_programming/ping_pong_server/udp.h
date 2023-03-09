#ifndef __UDP_H__
#define __UDP_H__

#include <stddef.h>
#include <sys/socket.h> 

int UdpOpenSocket(int port);

int UdpHandle(int sockfd, char *buf, size_t len, int port, const char *msg);

#endif /* __UDP_H__ */

