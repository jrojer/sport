from itertools import combinations
from random import randint


def f(comb):
    return sum(v for v, w in comb)/sum(w for v, w in comb)


def case(n, k):
    values = [randint(0, n) for i in range(n)]
    weights = [randint(1, n) for i in range(n)]
    items = list(zip(values, weights))
    return items


def solve(items, k):
    ans = 0
    for comb in combinations(items, k):
        s = f(comb)
        if s > ans:
            ans = s
            best_comb = comb
    return best_comb, ans


def main():
    n = 10 
    k = 4
    items = case(n, k)
    best, ans = solve(items, k)
    with open('input.txt','w') as fd:
        print(n,k,file=fd)
        for v,w in items:
            print(v,w,file=fd)
    print(items)
    print(best)
    print(ans)


#print(solve([(0, 3), (4, 2), (4, 5), (1, 4), (5, 3)],3))
main()
