import os

search_path = input("Enter directory path to search : ")
search_str = input("Enter the search string : ")

# Append a directory separator if not already present
if not (search_path.endswith("/") or search_path.endswith("\\") ): 
    search_path = search_path + "/"
                                                          
if not os.path.exists(search_path):
    print("no such path")

# Repeat for each file in the directory  
for root,dirs,files in os.walk(search_path):
    
    for name in files:
        with open(os.path.join(root,name)) as file:
            try:
                line = file.readline()
            except UnicodeDecodeError:
                continue
            # Loop until EOF
            while line != '' :
                # Search for string in line
                index = line.find(search_str)
                if ( index != -1) :
                    print(name)
                    break

                # Read next line
                try:
                    line = file.readline()
                except UnicodeDecodeError:
                    continue
                    
#grep -rnw '/path/to/somewhere/' -e 'pattern'