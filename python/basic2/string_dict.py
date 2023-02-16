#!/usr/bin/env python3

def str_dict(string):
    word_dict = {}
    for s in string:
        word_dict.update({s:string.count(s)})
    return word_dict
        
print(str_dict("razvaknin"))