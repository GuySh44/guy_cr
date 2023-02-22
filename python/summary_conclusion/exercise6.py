import re
def dunder_filter(key):
    if re.search("__.+__" ,key) is None:
        return True
    else:
        return False

test = "raz"
print("including dunder\n")
print(dir(test))

new_dir = list(filter(dunder_filter ,dir(test)))

new_dir_compre = [key for key in dir(test) if re.search("__.+__", key) is None]

print("\nwithout dunder regular\n")
print(new_dir)
print("\nwithout dunder comprehension\n")
print(new_dir_compre)