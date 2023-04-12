#include <stdio.h>
#include <stdlib.h> /* system */

#include "vpn_utils.h"

int run(char *cmd)
{
	printf("Execute '%s'\n", cmd);
	if (system(cmd))
	{
		return 1;
	}
	
	return 0;
}

sudo apt-get update
sudo apt-get install net-tools
sudo apt-get install wireshark
sudo apt-get install openssh-server 
sudo apt-get install curl
sudo apt install git
sudo apt install apache2
sudo apt-get install -y ca-certificates
sudo apt install libnss3-tools
sudo apt install python3-pip
sudo apt-get install python3-scapy
sudo apt install python-dev-is-python3 
sudo apt-get install chromium
sudo apt install libnss3-tools
sudo apt install inetutils-traceroute 
sudo apt install cgdb

