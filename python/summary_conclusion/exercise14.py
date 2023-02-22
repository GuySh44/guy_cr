class SNode():
    def __init__(self,value,next_node):
        self.next_node = next_node
        self.value = value
        
    @property
    def next_node(self):
        return self._next_node
    
    @next_node.setter
    def next_node(self, next_node):
        self.__dict__['_next_node'] = next_node
    
    @property
    def value(self):
        return self._value
    
    @value.setter
    def value(self, new_val):
        self.__dict__['_value'] = new_val
    
    def __repr__(self):
        return f'value: {self._value}\nnext node:\n  |\n  |\n{self._next_node}'
        

class SList():
    def __init__(self, *args):
        self.root = SNode("DUMMY",None)
        init_list = list(args)
        for elem in init_list:
            self.push(elem)
        
    def __setitem__(self, value):
        new_node = SNode(value, self.root)
        self.root = new_node
        
    def __delitem__(self, node):
        node.value = node.next_node.value
        node.next_node = node.next_node.next_node
    
    def push(self, value):
        self.__setitem__(value)
        
    def pop(self):
        value = self.root.value
        self.__delitem__(self.root)
        return value
    
    def remove(self, node):
        self.__delitem__(node)
    
    def __len__(self):
        node = self.root
        count = 0
        while node.next_node is not None:
            count += 1
            node = node.next_node
        return count
    
    def __iter__(self):
        current = self.root
        while current is not None:
            yield current
            current = current.next_node
            
    def __repr__(self):
        return f'{self.root}'
            
    
print("empty list basic check")
s_lst_empty = SList()
print(len(s_lst_empty))
print(bool(s_lst_empty))
print(s_lst_empty)
print()

print("reg list check")
s_lst = SList(1, "hello", (5, 6))
print("lst init")
print(s_lst)

print("lst len")
print(len(s_lst))
print()

for elem in s_lst:
    print(elem.value)
    if elem.value is 'hello':
        s_lst.remove(elem)
    print()
    
print("check if 'hello' removed\n")
print(s_lst)
print()

print("try to pop")
popped = s_lst.pop()
print(s_lst)
print(popped)
print()

print("check not empty by bool:")
print(bool(s_lst))