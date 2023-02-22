def print_dict(dct):
    for key, value in dct.items():
        print("{"+ str(key) + ":" + str(value) + "}")
        
dct = {0:'a', 1:'b', 3:'c', 2:'d'}
print(dct)
print_dict(dct)