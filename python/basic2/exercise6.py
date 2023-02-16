#!/usr/bin/env python3

def rot_left(lst, amount):
    print(lst[amount:] + lst[:amount])
    
list1 = [1,2,3,4,5,6]

rot_left(list1,1)

rot_left(list1,2)

rot_left(list1,3)