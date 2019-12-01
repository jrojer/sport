

def similar(a,b):
    i = 0
    j = 0
    res = 0
    while i < len(a) and j < len(b):
        if   a[i] <  b[j]: i += 1
        elif b[j] <  a[i]: j += 1
        elif a[i] == b[j]:
            k = a[i]
            while i < len(a) and a[i] == k: i+=1
            while j < len(b) and b[j] == k: j+=1
            res += 1
    return res


def difval(a, off=0):
    if len(a) <= off:
        return 0
    i = off
    res = 1
    prev = a[i]
    while i < len(a):
        if a[i] != prev:
            res += 1
            prev = a[i]
        i+=1
    return res


def different(a,b):
    i = 0
    j = 0
    res = 0
    while i < len(a) and j < len(b):
        if   a[i] <  b[j]:
            i += 1
            res += 1
        elif b[j] <  a[i]:
            j += 1
            res += 1
        elif a[i] == b[j]:
            k = a[i]
            while i < len(a) and a[i] == k: i+=1
            while j < len(b) and b[j] == k: j+=1
    res += difval(a,i)
    res += difval(b,j)
    return res


def test():
    assert similar([],[]) == 0
    assert similar([1],[]) == 0
    assert similar([1],[1]) == 1
    assert similar([1,1],[1,1]) == 1
    assert similar([1],[1,1]) == 1
    assert similar([1,2],[1,2,2]) == 2
    assert similar([1,2,2,3],[1,2,3]) == 3
    assert similar([1,2,2,3],[2,3]) == 2
    assert similar([1,2,3],[2,2,2,3,3,3,33]) == 2
    assert similar([1,2,3],[1,1,1,2,2,3,3,3,33]) == 3
    assert similar([1,2,3],[4]) == 0
    assert similar([1,2,3,4],[4]) == 1
    assert similar([1,2,3,4],[1,1,1]) == 1
    assert similar([1,2,3,4],[1,1,1,5,6]) == 1

    assert difval([1,2,3]) == 3
    assert difval([2,2,2]) == 1
    assert difval([]) == 0
    assert difval([2,2,2,3]) == 2

    assert different([1],[1,1,1]) == 0
    assert different([1,2,3],[1,2,3,4,4]) == 1
    assert different([1,2,3],[1,2,3,4,5]) == 2
    assert different([1,2,3],[1,2,3,4,5,6,6]) == 3


test()
