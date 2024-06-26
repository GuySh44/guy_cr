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

int InterfaceSetServerRouting()
{
	run("sysctl -w net.ipv4.ip_forward=1");
	run("iptables -t nat -A POSTROUTING -s 10.20.0.0/24 ! -d 10.20.0.0/24 -j MASQUERADE");
	run("iptables -A FORWARD -s 10.20.0.0/24 -m state --state RELATED,ESTABLISHED -j ACCEPT");
	run("iptables -A FORWARD -d 10.20.0.0/24 -j ACCEPT");
	return 0;
}

int InterfaceCleanServerRouting()
{
	run("iptables -t nat -D POSTROUTING -s 10.20.0.0/24 ! -d 10.20.0.0/24 -j MASQUERADE");
	run("iptables -D FORWARD -s 10.20.0.0/24 -m state --state RELATED,ESTABLISHED -j ACCEPT");
	run("iptables -D FORWARD -d 10.20.0.0/24 -j ACCEPT");
	return 0;

}
int InterfaceSetClientTable(char* local_addr, char* pub_addr, char* gateway)
{
	char cmd[BUFFER_SIZE];
	char substring1[BUFFER_SIZE];
	char substring2[BUFFER_SIZE];
	
	if(sprintf(substring1, "ip route add default via %s", local_addr) < 0)
	{
		return 1;
	}
	
	if(sprintf(substring2, " dev vpn0 metric 1") < 0)	
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
	
	
	if(sprintf(substring1, "ip route add %s", gateway) < 0)
	{
		return 1;
	}
	
	if(sprintf(substring2, " via 0.0.0.0 dev enp0s3") < 0)	
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

	if(sprintf(substring1, "ip route add %s", pub_addr) < 0)
	{
		return 1;
	}
	
	if(sprintf(substring2, " via %s", gateway) < 0)	
	{
		return 1;
	}
	
	strcat(substring1, substring2);
	
	if(sprintf(substring2, "/32 dev enp0s3") < 0)	
	{
		return 1;
	}
	
	if(sprintf(cmd, "%s", substring1) < 0)
	{
		return 1;
	}
	
	if(0 != run(cmd))
	{
		return 1;
	}
	
	run("sysctl -w net.ipv4.ip_forward=1");
	run("iptables -t nat -A POSTROUTING -o vpn0 -j MASQUERADE");
	run("iptables -I FORWARD 1 -i vpn0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
	run("iptables -I FORWARD 1 -o vpn0 -j ACCEPT");
}

int InterfaceCleanClientTable(char* local_addr, char* pub_addr, char* gateway)
{
	char cmd[BUFFER_SIZE];
	char substring1[BUFFER_SIZE];
	char substring2[BUFFER_SIZE];
	
	if(sprintf(substring1, "ip route del default via %s", local_addr) < 0)
	{
		return 1;
	}
	
	if(sprintf(substring2, " dev vpn0 metric 1") < 0)	
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
	
	
	if(sprintf(substring1, "ip route del %s", gateway) < 0)
	{
		return 1;
	}
	
	if(sprintf(substring2, " via 0.0.0.0 dev enp0s3") < 0)	
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

	if(sprintf(substring1, "ip route del %s", pub_addr) < 0)
	{
		return 1;
	}
	
	if(sprintf(substring2, " via %s", gateway) < 0)	
	{
		return 1;
	}
	
	strcat(substring1, substring2);
	
	if(sprintf(substring2, "/32 dev enp0s3") < 0)	
	{
		return 1;
	}
	
	if(sprintf(cmd, "%s", substring1) < 0)
	{
		return 1;
	}
	
	if(0 != run(cmd))
	{
		return 1;
	}
	run("iptables -t nat -D POSTROUTING -o vpn0 -j MASQUERADE");
	run("iptables -D FORWARD 1 -i vpn0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
	run("iptables -D FORWARD 1 -o vpn0 -j ACCEPT");

}
