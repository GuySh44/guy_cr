def lst_compreh():
    return [i if i%2 == 0 else "odd" for i in range(500)]

print(lst_compreh())