from random import randint
from numpy import base_repr

def gen(n,k):
    strings = []
    for i in range(n):
        random_string = base_repr(randint(1,10**(k-1)),36)
        strings.append(random_string)
        
    test = '{}\n{}'.format(len(strings),'\n'.join(strings))
    strings.sort()
    clue = '\n'.join(strings)
    
    return test,clue
    
    
def gen1(n,k):
    strings = []
    for i in range(n):
        strings.append('a'*k)
        
    test = '{}\n{}'.format(len(strings),'\n'.join(strings))
    #strings.sort()
    clue = '\n'.join(strings)
    
    return test,clue