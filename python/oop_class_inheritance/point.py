import numbers
import math

class Point:
    def __init__(self, x = 0.0, y = 0.0):
        if (not isinstance(x, numbers.Number)) or (not isinstance(y, numbers.Number)):
            print("wallak not number gever")
        else:
            self.x = x
            self.y = y
        
    def distance_from_origin(self):
        return math.sqrt((self.x)**2 + (self.y)**2)
        
p = Point(1, 2.5)
print(p.x)
print(p.y)
print(p.distance_from_origin())