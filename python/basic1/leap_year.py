def leap_year(year):
    num = int(year)
    return(num%4 == 0 and (num%400 == 0 or num%100 != 0))

print(leap_year(1))
print(leap_year(400))
print(leap_year(300))
print(leap_year(200))
print(leap_year(104))
