def check_is_prime(num):
    if num <= 1:
        return False
    for i in range(2,num):
        if num%i == 0:
            return False
    return True

print(check_is_prime(2))
print(check_is_prime(5))
print(check_is_prime(9))
print(check_is_prime(31))