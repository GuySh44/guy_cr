#!/usr/bin/env python3

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

list1 = [1,2,3,4]
list2 = [3,4,5,6]

list_contain1(list1,list2)

list_contain2(list1,list2)

list_contain3(list1, list2)