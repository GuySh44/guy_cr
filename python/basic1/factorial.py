def factorial(number):
    if(0 == number):
        return 1
    return (number * factorial(number-1))
    
print(factorial(5))