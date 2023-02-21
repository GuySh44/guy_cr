import numbers

class NotNumber(Exception):
    def __init__(self, value, message = 'is not a number'):
        self.value = value
        self.message = f'{self.value} ' + message
        super().__init__(self.message)

class ValidPoint: 
    def __set_name__(self, owner, name):
        self.property_name = name
        
    def __get__(self, instance, owner):
        if instance is None:
            return self
        return self.value or None
                
    def __set__(self, instance, value = 0.0):
        if not isinstance(value, numbers.Number):
            raise NotNumber(value)
        self.value = float(value)
        
    def __delete__(self, instance):
        pass
        
                
class Point: 
    '''
    implement a point class, using ValidPoint descriptor
    a point must be a number.
    '''
    x = ValidPoint()
    y = ValidPoint()        
    

p = Point()
p.x = 1
p.y = 2.3
print(p.y)
del p.y
print(p.y)
p.y = 'a'