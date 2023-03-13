#!/usr/bin/python3

from scapy.all import *

def sendtogateway(packet):
	global gatewaymac
	packet[Ether].src = Ether().src
	packet[Ether].dst = gatewaymac
	sendp(packet)
	
targetip = "192.168.6.11"
gatewayip = "192.168.6.1"
gatewaymac= getmacbyip(gatewayip)
while True:
	try:
		sniff(filter= "ip src host " + targetip, count = 1,  prn=sendtogateway)
	except:
		continue
