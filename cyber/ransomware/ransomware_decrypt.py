from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Util.Padding import unpad
import os

directory = '<path to dir>'

rsa_cipher = None
key_size = 32

def get_rsa():
    with open('<rsa private key>','r') as f:
        rsa_key = RSA.importKey(f.read())
    return PKCS1_OAEP.new(rsa_key)
    
def decrypt_file(file):
    global rsa_cipher
    global key_size
    with open(file,'rb') as f:
        enc_data = f.read()
    enc_key = enc_data[0:256]
    key = rsa_cipher.decrypt(enc_key)
    iv = enc_data[256:256+AES.block_size]
    cipher = AES.new(key, AES.MODE_CBC, iv)
    data = unpad(cipher.decrypt(enc_data[256+AES.block_size:]), key_size)
    with open(file.replace(".enc",""),'wb') as f:
        f.write(data)
    
def main():
    global rsa_cipher
    rsa_cipher = get_rsa()
    for filename in os.listdir(directory):
        file = os.path.join(directory, filename)
        if os.path.isfile(file) and ".enc" in file:
            decrypt_file(file)
            os.remove(file)
        
        
if __name__ == "__main__":
    main()
