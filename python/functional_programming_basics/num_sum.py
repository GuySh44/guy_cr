import functools

def sum_for(lst):
    lst_sum = 0
    for elm in lst:
        lst_sum += elm
    return lst_sum

def sum_reduce(lst):
    lst_sum = functools.reduce(lambda a, b: a+b, lst)
    return lst_sum

def sum_sum(lst):
    return sum(lst)

lst = [1, 2, 3, 4]
print(sum_for(lst))
print(sum_reduce(lst))
print(sum_sum(lst))