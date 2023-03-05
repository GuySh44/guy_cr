#!/usr/bin/env python3

import socket
import subprocess
import sys


target_ip = input("Enter host IP to scan: ")
port_range = input("Enter port range: (x,y,a-b)")
#create list of ranges
port_list = port_range.split(",")
#split ranges into sublists
port_list = [rng.split("-") for rng in port_list]


try:
#run on sublists
    for sub_list in port_list:
        start_port = int(sub_list[0])
        try:
            end_port = int(sub_list[1]) + 1
        except IndexError:
            end_port = start_port+1
#run on ports of each sublist
        for port in range(start_port, end_port+1):  
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            result = sock.connect_ex((target_ip, port))
            if result == 0:
                print ("Port {}: 	 Open".format(port))
            sock.close()

except KeyboardInterrupt:
    print ("Keyboard Interrupt exit")
    sys.exit()

except socket.error:
    print ("Couldn't connect to host")
    sys.exit()
