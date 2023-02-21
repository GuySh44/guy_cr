class X:
    def __init__(self, a):
        self.a = a
        
    def __getattr__(self, attr):
        return print(attr + " doesn't exist")

print(X(1).a)
X(1).b

x = X(1)