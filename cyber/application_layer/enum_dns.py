import socket
target = input("Enter target url:\n")

with open("./dict.txt", "r") as file:
    for word in file:
        url = str(word).replace("\n","") + "." + str(target)
        try:
            name = socket.gethostbyname_ex(url)
            print(name)
        except socket.gaierror as e:
            continue
        except KeyboardInterrupt:
            exit()