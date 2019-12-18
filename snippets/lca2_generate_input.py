

from random import randint

def generate(filename):
    n = 2 * 10**5 - 1
    with open(filename, 'w') as fd:
        print(n, file = fd)
        for i in range(1,n):
            print(i, file = fd)
        print(n, file = fd)
        for i in range(1,n+1):
            u = randint(1,n)
            v = randint(1,n)
            print(u,v, file = fd)

generate('lca2_large_input.txt')




        