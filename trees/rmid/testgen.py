from random import randint
from random import shuffle

test = [1]
clue = []

size = 20

actions = [randint(1,100) for x in range(size)] + [-1]*(size//2)
shuffle(actions)
array = []

for act in actions:
    if act == -1:
        if array:
            m = array.pop((len(array)-1)//2)
            clue.append(m)
            test.append(act)
    else:
        array.append(act)
        array.sort()
        test.append(act)

test.append(0)

with open('gen_input.txt','w') as fd:
    fd.write('\n'.join(map(str,test)))

with open('gen_output.txt','w') as fd:
    fd.write('\n'.join(map(str,clue)))
        


