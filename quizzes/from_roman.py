def calc_end(end):
    end_str = str(end)
    if(end_str[0] == 'V'):
        return 4 + len(end_str)
    else:
        if (end_str[-1] == 'I'):
            return len(end_str)
        elif (end_str[-1] == 'V'):
            return 4
        else:
            return 9

def from_roman(num):
    summ = 0
    for i,char in enumerate(str(num)):
        if char in ['I', 'V']:
            summ += calc_end(str(num)[i:])
            break
        else:
            if char == 'X':
                summ += 10
            elif char == 'L':
                summ += 50
            elif char == 'C':
                summ += 100
            elif char == 'D':
                summ += 500
            elif char == 'M':
                summ += 1000
    return summ
             
    
print(from_roman("IV"))
print(from_roman("MMDXVIII"))