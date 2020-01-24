from random import randint

def generate(n,k):
    a = [randint(-100,100) for i in range(n)]
    r = [randint(-90,90) for i in range(k)]
    return a,r


def solve(array,reqs):
    res = []
    for r in reqs:
        try:
            res.append(array.index(r))
        except ValueError:
            res.append('not found')
    return res


a,r = generate(200,60)
ans = solve(a,r)

test = '{}\n{}\n{}\n{}'.format(len(a),' '.join(map(str,a)),len(r),'\n'.join(map(str,r)))

clue = '\n'.join(map(str,ans))

print(test)
print()
print(clue)
