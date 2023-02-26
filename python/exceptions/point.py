import numbers
import unittest

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

class TestPointMethods(unittest.TestCase):
    
    def test_creation(self):
        self.assertIsNotNone(p)
        
    def test_x(self):
        self.assertEqual(p.x, 1)
    
    def test_y(self):
        self.assertEqual(p.y, 2.3)
        
    def test_del(self):
        del p.y
        self.assertEqual(p.y, 2.3)
        
    def test_err(self):
        with self.assertRaises(NotNumber):
            p.y = 'a'
        
        
if __name__ == '__main__':
    unittest.main()