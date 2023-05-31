import socket


def server_program():
    host = socket.gethostname()
    port = 8080 

    server_socket = socket.socket() 
    
    server_socket.bind((host, port)) 
    server_socket.listen(2)
    
    conn, address = server_socket.accept() 
    
    print("Connection from: " + str(address))
    
    while True:
        data = conn.recv(1024).decode()
        if not data:
            break
            
        print("from connected user: " + str(data))
        
    conn.close()


if __name__ == '__main__':
    server_program()