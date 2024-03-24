#!/usr/bin/env python3
def add_five(num):
	found = 0
	is_neg = 0
	str_num = str(num)
	
	if(num < 0):
		str_num = str_num[1:]
		is_neg = 1
		str_num = str_num[::-1]
	
	num_lst = [ch for ch in str_num]
	
	for i, ch in enumerate(str_num):
		if(int(ch) <= 5):
			num_lst[i] = '5'
			found = 1
			break
		

	if(found == 0):
		num_lst[-1] = '5'
	
	new_num = "".join(num_lst)
	
	if(is_neg):
		new_num = new_num[::-1]
		new_num = "-" + new_num
		
	return new_num
	
print("1123 " + add_five(1123)) 
print("-1123 " + add_five(-1123)) 

print("5555 " + add_five(5555)) 
print("-5555 " + add_five(-5555)) 

print("4545 " + add_five(4545)) 
print("-4545 " + add_five(-4545)) 

print("4444 " + add_five(4444)) 
print("-4444 " + add_five(-4444))

print("6666 " + add_five(6666)) 
print("-6666 " + add_five(-6666))  
