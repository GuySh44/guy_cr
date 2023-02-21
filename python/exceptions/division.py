def div(a, b):
    try:
        return a/b 
    except TypeError:
        print("ayo thats not a division type")
        raise TypeError("shaggy this aint a division type")
    except ZeroDivisionError:
        print("tried to divide by zero")
        return None
    
print(div(1,0))
print(div(5,2))
print(div('a',2))