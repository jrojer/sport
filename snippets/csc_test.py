
def solve(d,m,a):
    a = [0] + a + [d]
    pos = 0
    ans = 0
    i = 0
    while pos + m < d:
        while a[i+1] <= pos+m:
            i+=1
        if a[i] > pos:
            pos = a[i]
        else:
            ans = -1
            break
        ans += 1
    return ans


def test():
    print(solve(500,200,[100,200,300,400]) == 2)
    print(solve(700,200,[100,200,300,400]) == -1)
    print(solve(5,7,[1,2,3,4]) == 0)
    print(solve(5,1,[1,2,3,4]) == 4)
    print(solve(80,50,[1,2,30,60]) == 1)
    print(solve(110,50,[1,2,30,60]) == 2)
    print(solve(60,59,[1,2,30,60]) == 1)
    print(solve(600,59,[1,2,300,599]) == -1)
    print(solve(2,1,[1]) == 1)
    print(solve(2,2,[1]) == 0)
    print(solve(2,1000,[1]) == 0)
    print(solve(1000,1,list(range(1,1000))) == 999)
    print(solve(6,1,[1,2,3,5]) == -1)


def main():
    d = int(input())
    m = int(input())
    n = int(input())
    a = list(map(int,input().split()))
    ans = solve(d,m,a)
    print(ans)

test()
#main()


