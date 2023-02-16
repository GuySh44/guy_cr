#!/usr/bin/env python3

def enum_list(lst):
    for i, elem in enumerate(lst):
        print(str(i) + " " + str(elem))

def enum_dict(dic):
    for key, elem in dic.items():
        print(str(key) + " " + str(elem))

        
lst = ['a' , 'b' , 'c']
dic = {'a':1, 'b':2, 'c':3}

enum_list(lst)
enum_dict(dic)