#!/usr/bin/env python3

list_while = []
list_for = []
list_range = []

for i in range(51):
    list_for = list_for + [i*2]

i = 0
while i < 51:
    list_while = list_while + [i*2]
    i = i + 1

list_range.extend(range(0,101,2))

print(list_while)
print(list_for)
print(list_range)