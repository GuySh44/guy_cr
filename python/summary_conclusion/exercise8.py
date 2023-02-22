def rem_nonstr(lst):
    for elem in lst:
        if isinstance(elem, str):
            lst.remove(elem)
            
lst = [1,2,3,"4",5,"a"]
print(lst)
rem_nonstr(lst)
print(lst)