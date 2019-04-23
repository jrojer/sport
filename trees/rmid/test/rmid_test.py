# coding: utf-8
from random import randint, shuffle


def solve(vals):
    arr = []
    ans = []
    progress = 0
    for v in vals:
        if v == -1:
            ans.append(arr.pop((len(arr)-1)//2))
        else:
            arr.append(v)
            arr.sort()
        if progress % (len(vals)//10) == 0:
            print(progress/len(vals) * 100)
        progress += 1
    return ans   


def rmid_test(num_vals,num_reqs,a,b):
    size = 0
    values = [randint(a,b) for x in range(num_vals)]
    values.extend([-1]*num_reqs)
    shuffle(values)
    for i in range(len(values)):
        if values[i] == 0 or (values[i] == -1 and size == 0): 
            values[i] = randint(1,b)
            size += 1
        elif values[i] == -1:
            size -= 1
        else:
            size += 1

    answer = solve(values)

    with open('rmid_test_ans.txt','w') as fd:
        for v in answer:
            print(v,file=fd)
    with open('rmid_test.txt','w') as fd:
          print(1,file=fd)
          for v in values:
              print(v,file=fd)
          print(0,file=fd)
          
