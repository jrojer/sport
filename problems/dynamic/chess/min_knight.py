
def min_knight(n,m):
    table = [[-1 for i in range(m+1)] for j in range(n+1)]
    table[1][1] = 0
    fifo = [(1,1)]
    while fifo:
        i,j = fifo.pop(0)
        for si, sj in ((-2,1),(-1,2),(1,2),(2,1),(2,-1),(1,-2),(-1,-2),(-2,1)):
            ni = i + si
            nj = j + sj
            if 1 <= ni <= n and 1 <= nj <= m:
                if table[ni][nj] == -1 or table[ni][nj] > table[i][j] + 1:
                    table[ni][nj] = table[i][j] + 1
                    fifo.append((ni,nj))

    '''
    for i in range(1,n+1):
        for j in range(1,m+1):
            print('{:3d}'.format(table[i][j]),end='')
        print()
    '''
    return table[n][m]


print(min_knight(2022,2022))



