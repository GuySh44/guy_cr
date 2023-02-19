def print_content_empty(path):
    f = open(path, "r")
    try:
        print(f.read().upper())
    finally:
        f.close()
        
def print_content_manager(path):
    with open(path, "r") as f:
        print(f.read().upper())
        

print_content_empty('./test.txt')
print_content_manager('./test.txt')
        