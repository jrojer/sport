# coding: utf-8
t='0.'+''.join(map(str,fraq(123456788,123456789,10**6-1)))
def fraq(x,d,n):
    res = []
    for i in range(n):
        q = x//d
        r = x%d
        x = r*10
        res.append(q)
    return res
    
