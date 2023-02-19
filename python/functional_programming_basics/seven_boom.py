def seven_for(num):
    lst = []
    for i in range(num):
        if (i % 7 != 0) and ('7' not in str(i)):
            lst.append(i)
    return lst

def seven_compreh(num):
    return [i for i in range(num) if (i % 7 != 0) and ('7' not in str(i))]

def seven_map(num):
    def seven_boom(i):
        if (i % 7 != 0) and ('7' not in str(i)):
            return i
    
    lst = list(map(seven_boom, list(range(num))))
    return [i for i in lst if i is not None]
    

print(seven_for(100))
print(seven_compreh(100))
print(seven_map(100))