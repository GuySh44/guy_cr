def print_enum(lst):
    for i, elem in enumerate(lst):
        print("list[" +str(i)+"] = " + str(elem))
        
lst = [5,4,3,2,1,0]
print(lst)
print_enum(lst)