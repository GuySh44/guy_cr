def dict_from_list(lst):
    dct = {}
    for index, elem in enumerate(lst):
        dct.update({index:elem})
    return dct
        
print(dict_from_list(['a','b','c']))