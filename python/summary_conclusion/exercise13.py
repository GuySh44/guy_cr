def infi_sqr_gen(n):
    value = 0
    
    while value < n:
        yield value**2
        
        value += 1
        
for value in infi_sqr_gen(10):
    print(value)