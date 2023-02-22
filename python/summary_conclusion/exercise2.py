def file_capital(path):
    with open(path, "r") as file:
        buffer = file.read()
    with open(path, "w") as file:
        file.write(buffer.upper())
        
file_capital("./test.txt")