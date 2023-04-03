#include <linux/if.h>
#include <linux/if_tun.h>
#include <string.h>
#include <assert.h>
#include <stddef.h> /**/
#include <fcntl.h> /* open */
#include <unistd.h> /* close */
#include <sys/ioctl.h> /* ioctl */
#include <stdio.h>


#include "interface.h"
#include "vpn_utils.h"

#define BUFFER_SIZE 1024

int InterfaceCreate()
{
	struct ifreq ifr;
	int fd = 0, retval = 0;
	if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
	{
		return fd;
	}
	
	memset(&ifr, 0, sizeof(ifr));
	
	
	ifr.ifr_flags = IFF_TUN;
	strncpy(ifr.ifr_name, "vpn0", IFNAMSIZ);
	
	if ((retval = ioctl(fd, TUNSETIFF, (void*) &ifr)) < 0)
	{
		close(fd);
		return retval;
	}
	
	return fd;
}

int InterfaceSet(char* addr, int mtu)
{
	char cmd[BUFFER_SIZE];
	char substring1[BUFFER_SIZE];
	char substring2[BUFFER_SIZE];
	
	assert(addr);
	
	if(sprintf(substring1, "ifconfig vpn0 %s", addr) < 0)
	{
		return 1;
	}
	
	if(sprintf(substring2, " mtu %d up", mtu) < 0)
	{
		return 1;
	}
	
	strcat(substring1, substring2);
	if(sprintf(cmd, "%s", substring1) < 0)
	{
		return 1;
	}
	
	if(0 != run(cmd))
	{
		return 1;
	}
	
	return 0;
}

int InterfaceRecieve(int tunfd, void *buf, size_t len)
{
	return read(tunfd, buf, len);
}

int InterfaceRespond(int tunfd, void *msg, size_t msg_len)
{
	return write(tunfd, msg, msg_len);
}
