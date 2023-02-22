class DefaultDict(dict):
    def __init__(self,default):
        self.default = default
        super().__init__(self)
        
    def __missing__(self,key):
        return self.default


d = DefaultDict(0)
d['a'] = "hello"
print(d)
print(d['b'])
print(d[2])
print(d.items())