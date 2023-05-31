import syslog
import socket

host = socket.gethostname()
port = 8080


def connect_remote():
    client_socket = socket.socket() 
    client_socket.connect((host, port))
    return client_socket
    
def push_remote(log, client_socket):
    message = log
    client_socket.send(message.encode())

def parse_log(log):
    if 'debug' in log:
        priority = syslog.LOG_DEBUG
    elif 'info' in log:
        priority = syslog.LOG_INFO
    elif 'notice' in log:
        priority = syslog.LOG_NOTICE
    elif 'warning' in log:
        priority = syslog.LOG_WARNING
    elif 'error' in log:
        priority = syslog.LOG_ERR
    elif 'critical' in log:
        priority = syslog.LOG_CRIT
    elif 'alert' in log:
        priority = syslog.LOG_ALERT
    elif 'emergency' in log:
        priority = syslog.LOG_EMERG
    else:
        priority = syslog.LOG_DEBUG
    return priority

def main():
    client_socket = connect_remote()
    while(True):
        priority = None
        log = input("Enter log: ")
        if('exit' == log):
           break 
        else:
            priority = parse_log(log)
    
        syslog.syslog(priority, log)
        
        if priority < syslog.LOG_WARNING:
            push_remote(log, client_socket)
        
    syslog.closelog()
        
if __name__ == "__main__":
    main()