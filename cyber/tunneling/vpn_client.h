#ifndef __VPN_CLIENT_H__
#define __VPN_CLIENT_H__

int ParseMessage(char *buf, char *msg);

int CloseFds(int frst_fd, int scnd_fd);

#endif /* __VPN_CLIENT_H__ */
