def horse_lazy(m, n):
    def recurse(x, y, M):
        if not (0 <= x < m and 0 <= y < n):
            return 0
        if M[x][y] > -1:
            return M[x][y]
        s = 0
        for nx, ny in ((x - 2, y + 1), (x - 2, y - 1), (x - 1, y - 2), (x + 1, y - 2)):
            s += recurse(nx, ny, M)
        M[x][y] = s
        return s

    M = [[-1 for i in range(n)] for i in range(m)]
    M[0][0] = 1
    return recurse(m - 1, n - 1, M)

print(horse_lazy(3,3))