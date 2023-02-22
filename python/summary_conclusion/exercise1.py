def return_name(path):
    lst = path.split('/')
    return lst[-1]


print(return_name("/raz/or/ravid/guy/daniel.py"))