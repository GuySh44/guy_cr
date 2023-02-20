def if_name(*args, **kwargs):
    if 'name' in kwargs:
        print(kwargs.get('name'))
    else:
        print("no name was passed")
        
if_name(1, 2, 3, name="hello")
if_name("hello")