# coding: utf-8
from itertools import permutations

def num_selection_swaps(a):
    num_swaps = 0
    a = list(a)
    n = len(a)
    for i in range(n):
        m=i
        for j in range(i+1,n):
            if a[m]>a[j]:
                m = j
        if m != i:
            a[m],a[i] = a[i],a[m]
            num_swaps += 1
    return num_swaps


def bubblesort_swaps(a):
    a = list(a)
    n = len(a)
    num_swaps = 0
    for i in range(1,n):
        swap = False
        for j in range(1,n-i+1):
            i-=1
            j-=1
            if a[j+1]<a[j]:
                a[j+1],a[j] = a[j],a[j+1]
                swap = True
        num_swaps += 1 if swap else 0
    return num_swaps == n-1


def find_best_permutation_selection(N):
    m = 0
    res = [None]
    for p in permutations(range(N)):
        n = num_selection_swaps(p)
        if n > m:
            res[0] = p
            m = n
    for p in permutations(range(N)):
        n = num_selection_swaps(p)
        if n == m and p != res[0]:
            res.append(p)
    return res,m,len(res)


def find_best_permutation_bubble(N):
    res = []
    for p in permutations(range(N)):
        if bubblesort_swaps(p):
            res.append(p)
    return res,len(res)

