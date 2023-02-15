def flip_int(num):
    if(int(num) < 0):
        string = str(num)[0] + str(num)[-1:0:-1]
    else:
        string = str(num)[::-1]
    print(string)
    
flip_int(123)
flip_int(12.2)
flip_int("123")
flip_int(-123)
flip_int("-123")