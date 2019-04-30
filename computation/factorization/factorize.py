
def factorize(n):
    res = []
    k = n
    l = 2
    while k > 1:
        while k%l > 0:
            l+=1
        res.append(l)
        k /= l
    return res


def isprime(n):
    i = 2
    while(i*i <= n):
        if n % i == 0:
            return False
        i += 1
    return True
    

