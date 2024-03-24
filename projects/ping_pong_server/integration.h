#ifndef __INTEGRATION_H__
#define __INTEGRATION_H__

int ParseMessage(char *buf, char *msg);

int CloseFds(int tcpfd, int udpfd, int *clients_fds);

#endif /* __INTEGRATION_H__ */
