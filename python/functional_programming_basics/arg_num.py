def args_num(*args):
    count = 0
    for arg in args:
        count += 1
    return count

print(args_num())
print(args_num(1))
print(args_num(1, 2))
print(args_num(1, 2, 3))