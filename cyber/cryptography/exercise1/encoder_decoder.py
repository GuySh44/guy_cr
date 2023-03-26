#LUT table
BASE64_LUT = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"


def base64_encode(msg):
    #turn text into binary string
    bin_msg = ''.join(format(ord(char), '08b') for char in msg)
    #pad with trailing zeros
    bin_msg = bin_msg + '0' * ((6-(len(bin_msg) % 6)) % 6)
    #split into list of 6bit binary numbers, turn into integers
    bin_list = [int(bin_msg[i:i+6],2) for i in range(0, len(bin_msg), 6)]
    #turn integers into corresponding BASE64 chars, add trailing '='
    base64 = "".join([BASE64_LUT[int(i)] for i in bin_list]) + ('=' * ((3 - len(msg) % 3)%3))
    return base64
    
def base64_decode(msg):
    #get rid of trailing '='
    dec_msg = [BASE64_LUT.index(i) if i != '=' else None for i in msg] 
    #get rid of 'None's
    dec_msg = [i for i in dec_msg if i is not None]
    #turn base64 chars back into 6bit binary numbers
    bin_list = [str(format(i,'06b')) for i in dec_msg]
    #put list into a binary string
    bin_str = ''.join(bin_list)
    #get rid of padding zeros
    bin_str = bin_str[0:len(bin_str) - ((len(bin_str) % 8) % 8)]
    #turn bytes into text equivalant
    char_list = [chr(int(bin_str[i:i+8],2)) for i in range(0, len(bin_str), 8)]
    #join list into text
    text = "".join(char_list)
    return text

print(base64_encode("abccddd"))
print(base64_decode(base64_encode("abccddd")))