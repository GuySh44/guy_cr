def make_adder(first):
    def adder(second):
        return first + second
    return adder


add_3 = make_adder(3)
print(add_3(5))

print(add_3(3))

add_7 = make_adder(7)
print(add_7(1))
print(add_7(-3))