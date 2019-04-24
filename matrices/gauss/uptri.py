
eps = 0.000001

def ToUpperTriangle(matrix):
    M = matrix[:]
    nrows = len(M)
    ncols = len(M[0])
    i = 0
    while i < nrows and i < ncols:
        for k in range(i,nrows):
            if abs(M[k][i]) > eps:
                M[k],M[i] = M[i],M[k]
                break
        if abs(M[i][i]) < eps:
            break
        for k in range(i+1,nrows):
            a = M[k][i];
            b = M[i][i];
            for j in range(i,ncols):
                M[k][j] -= M[i][j] * a / b
        i += 1    
    return M


def ReadInput():
    n,m = map(int,input().split())
    matrix = []
    for i in range(n):
        matrix.append(list(map(float,input().split())))
    return matrix

    
def PrintRow(row):
    row = ['{:.1f}'.format(round(x if abs(x) > eps else 0,1)) for x in row]
    print(' '.join(row))


def PrintOutput(m):
    for r in m:
        PrintRow(r)


PrintOutput(ToUpperTriangle(ReadInput()))
