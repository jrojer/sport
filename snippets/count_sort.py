def count_sorted(arr):
    freq = [0]*11
    for x in arr:
        freq[x]+=1
    for i in range(1,len(freq)):
        freq[i] += freq[i-1]
    ans = [0]*len(arr)
    for x in arr:
        ans[freq[x]-1] = x
        freq[x]-=1
    return ans

import numpy as np

def test():

    for i in range(100):
        arr = np.random.randint(1,11,np.random.randint(0,20,1)).tolist()
        if count_sorted(arr) != sorted(arr):
            print(arr)
            break
    else:
        print('OK')

input()
print(' '.join(map(str,count_sorted(list(map(int,input().split()))))))
