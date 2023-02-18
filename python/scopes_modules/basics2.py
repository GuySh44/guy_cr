#!/usr/bin/env python3

def str_dict(string):
    word_dict = {}
    for s in string:
        word_dict.update({s:string.count(s)})
    return word_dict

def enum_list(lst):
    for i, elem in enumerate(lst):
        print(str(i) + " " + str(elem))

#instead of using enum and printing index and element, i print key and value
def enum_dict(dic):
    for key, elem in dic.items():
        print(str(key) + " " + str(elem))

        
def list_contain1(list1, list2):
    list3 = []
    for elem in list1:
        if elem in list2:
            list3 += [elem]
    print(list3)

    
def list_contain2(list1, list2):
    list3 = list(set(list1).intersection(list2))
    print(list3)
    
def list_contain3(list1, list2):
    print([elem for elem in list1 if elem in list2])

def rot_left(lst, amount):
    print(lst[amount:] + lst[:amount])
    

if __name__ == '__main__':
    print("std_dict test: ")
    str_dict("razvaknin")
    
    lst = ['a' , 'b' , 'c']
    dic = {'a':1, 'b':2, 'c':3}
    print("enum list test:")
    enum_list(lst)
    print("enum list test:")
    enum_dict(dic)

    list1 = [1,2,3,4]
    list2 = [3,4,5,6]
    print("list_contain1 test:")
    list_contain1(list1,list2)
    print("list_contain2 test:")
    list_contain2(list1,list2)
    print("list_contain3 test:")
    list_contain3(list1, list2)
    
    list1 = [1,2,3,4,5,6]
    print("rotate 1 left test:")
    rot_left(list1,1)
    print("rotate 2 left test:")
    rot_left(list1,2)
    print("rotate 3 left test:")
    rot_left(list1,3)