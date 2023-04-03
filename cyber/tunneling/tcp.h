#ifndef __TCP_H__
#define __TCP_H__

#include <stddef.h>

int TcpOpenSocket(int port);

int TcpAccept(int tcpfd, int port);

int TcpRespond(int clientfd, void *msg, size_t msg_len);

int TcpDisconnect(int socketfd);

int TcpRecieve(int sockfd, void *buf, size_t len);

int TcpConnectClient(char *srv_addr, int srv_port);

#endif /* __TCP_H__ */
