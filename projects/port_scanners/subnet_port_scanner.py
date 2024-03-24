#!/usr/bin/env python3

import socket
import subprocess
import sys

target_network = input("Enter Network IP to scan: (subnet 8)")
port = input("Enter port: ")

target_network = target_network.split(".")
target_network[1:4] = ['0'] * 3
try:
    for i in range(0, 256):
        target_network[1] = str(i)
        for j in range(0, 256):
            target_network[2] = str(j)
            for k in range(0, 256):
                target_network[3] = str(k)
                target_ip = (".").join(target_network)
                sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                result = sock.connect_ex((target_ip, int(port)))
                if result == 0:
                    print (f'IP: {target_ip} - Port {port}: 	 Open')
                sock.close()

except KeyboardInterrupt:
    print ("Keyboard Interrupt exit")
    sys.exit()

except socket.error:
    print ("Couldn't connect to host")
    sys.exit()
