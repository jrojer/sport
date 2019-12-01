

def slow(A):
    d = [0] * len(A)
    prev = [0] * len(A)
    for i in range(len(A)):
        d[i] = 1
        for j in range(i):
            if A[i] <= A[j] and d[j] + 1 > d[i]:
                d[i] = d[j] + 1
                prev[i] = j
    k = max(d)
    ans = []
    p = max(range(len(A)), key=lambda i: d[i])
    for i in range(k):
        ans.append(p + 1)
        p = prev[p]
    #print(k)
    #print(' '.join(map(str, ans[::-1])))
    return ans[::-1]


