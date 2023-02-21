class X:
    def __init__(self, a):
        self.__dict__['a'] = a
        
    def __setattr__(self, name, value):
        if name not in dir(self):
            raise TypeError(name + " is not an attribute")
        object.__setattr__(self, name, value)
        
x = X(1)
print(x.a)

#x.b = 2

class X:
    __slots__ = ['a']
    
    def __init__(self, a):
        self.a = a

x = X(1)
print(x.a)

x.b = 2