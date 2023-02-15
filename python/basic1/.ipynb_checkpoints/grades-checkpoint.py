def grades(numeric):
    if(numeric in range(0,10)):
        print('F')
    elif(numeric in range(10,30)):
        print('E')
    elif(numeric in range(30,50)):
        print('D')
    elif(numeric in range(50,70)):
        print('C')
    elif(numeric in range(70,90)):
        print('B')
    elif(numeric in range(90,101)):
        print('A')
        
grades(0)
grades(10)
grades(20)
grades(30)
grades(45)
grades(50)
grades(66)
grades(70)
grades(85)
grades(90)
grades(95)
grades(100)