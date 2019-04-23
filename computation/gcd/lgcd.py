# coding: utf-8
def lgcd(a,b):
    if a == 0:
        return 0,1
    if b == 0:
        return 1,0
    q = []
    while b:
        q.append(a//b)
        b,a = a%b,b
    q.pop()
    x = 0
    y = 1
    while q:
        x,y = y,x-y*q.pop()
    return x,y
        
def gcd(a,b):
    while a:
        a,b = b%a,a
    return b

def lgcd_test():
    from random import randint as r
    ok = 0
    failed = 0
    for i in range(100):
        a = r(0,1000)
        b = r(0,1000)
        x,y = lgcd(a,b)
        if x*a+y*b == gcd(a,b):
            #print('OK')
            ok += 1
        else:
            #print('FAILED',a,b)
            failed += 1
    print('ok',ok,'failed',failed)

lgcd_test()
#lgcd(668,82)

