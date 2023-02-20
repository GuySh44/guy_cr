def list_to_dict_compreh(lst):
    dct = {index: elem for index,elem in enumerate(lst)}
    return dct
    
def list_to_dict_no(lst):
    dct = {}
    for index,elem in enumerate(lst):
        dct.update({index:elem})
    return dct
    
print(list_to_dict_compreh(['a', 'b', 'c']))
print(list_to_dict_no(['a', 'b', 'c']))