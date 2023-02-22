def lst_inc(lst):
    for i,elem in enumerate(lst):
        lst[i] += 1
        
lst = [1,2,3,4]
print(lst)
lst_inc(lst)
print(lst)