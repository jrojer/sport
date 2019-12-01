from random import randint


def testgen(n, k, min_ai, max_ai):
    a = [randint(min_ai,max_ai) for i in range(n)]
    req = [(randint(0,len(a)),randint(min_ai,max_ai)) for j in range(k)]

    test = '{}\n{}\n{}\n{}'.format(
            n,
            ' '.join(map(str,a)),
            k,
            '\n'.join('{} {}'.format(i,x) for i,x in req))

    return test

if __name__ == '__main__':
    import sys
    if len(sys.argv) < 6:
        print('num args < 6')
        sys.exit()
    i = sys.argv[1]
    n,k,a,b = map(int,[sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5]])
    with open('testgen_{}.txt'.format(i),'w') as fd:
        fd.write(testgen(n,k,a,b))
    

    