import numpy as np

def testgen(n, k, min_ai, max_ai):
    a = np.random.randint(min_ai,max_ai,(n,k))
    test = '{} {}\n{}\n'.format(n,k, '\n'.join(' '.join(map(str,row)) for row in a))
    return test

if __name__ == '__main__':
    import sys
    if len(sys.argv) < 6:
        print('num args < 6')
        sys.exit()
    i = sys.argv[1]
    n,k,a,b = map(int,[sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5]])
    t = testgen(n,k,a,b)
    with open('testgen_{}.txt'.format(i),'w') as fd:
        fd.write(t)

    
