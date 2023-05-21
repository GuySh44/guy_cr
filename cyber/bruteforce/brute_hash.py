from hashlib import *
from time import time
import string
import itertools

def main():
    hash_func = int(input("Enter 1 for sha256 or 2 for sha1\n"))
    if(1 == hash_func):
        hash_func = sha256
    elif(2 == hash_func):
        hash_func = sha1
    else:
        print("wrong option\n")
        return 1
    
    num_char = input("Enter number of characters in password\n")
    
    char_set = []
    composition = int(input("Enter 1 for lowercase, 2 for digits, 3 for alphanumeric\n"))
    if(1 == composition):
        char_set = list(string.ascii_lowercase)
    elif(2 == composition):
        char_set = [str(i) for i in range(10)]
    elif(3 == composition):
        char_set = [str(i) for i in range(10)] + list(string.ascii_lowercase)
    else:
        print("wrong option\n")
        return 1
        
    password = input("Enter the password\n")
    
    print("cracking:")
    
    time_0 = time()
    
    hashed_pass = hash_func(password.encode('utf-8')).hexdigest()
    
    for guess in itertools.product("".join(char_set), repeat=int(num_char)):
        if (hashed_pass == hash_func("".join(guess).encode('utf-8')).hexdigest()):
            print("password is: " + "".join(guess))
            break
    
    time_1 = time()
    
    print("total time: " + str(time_1 - time_0))
    
    return 0

if __name__ == "__main__":
    main()