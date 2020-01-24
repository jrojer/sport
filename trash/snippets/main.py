

nv,ne = map(int,input().split())

M = [[0 for i in range(nv)] for j in range(nv)]

for i in range(ne):
    u,v = map(int,input().split())
    u -= 1
    v -= 1
    M[u][v] += 1
    M[v][u] += 1


def check_connectivity():
    visited = [False]*nv
    def dfs(v):
        visited[v] = True
        for u in range(nv):
            if M[v][u] > 0 and not visited[u]:
                dfs(u)
    dfs(0)
    return visited == [True]*nv


def check_parity():
    for i in range(nv):
        s = sum(M[i])
        if s>0 and s % 2 > 0:
            return False
    return True


def get_path():
    start = 0
    for i in range(nv):
        if sum(M[i]) > 0:
            start = i
            break
    else:
        return []

    path=[start]
    while True:
        v = path[-1]
        for u in range(nv):
            if M[v][u] > 0:
                M[v][u] -= 1
                M[u][v] -= 1
                path.append(u)
                break
        if path[0] == path[-1]:
            break

    return path


def main():
    if check_connectivity() == False or check_parity() == False:
        print('NONE')
        return


    paths = []
    p = get_path()
    while p:
        paths.append(p)
        p = get_path()


    while len(paths) > 1:
        for i in range(len(paths)):
            for j in range(i+1,len(paths)):
                if paths[j][0] in paths[i]:
                    idx = paths[i].index(paths[j][0])
                    a = paths[i][:, idx]
                    a.extend(paths[j])
                    a.extend(paths[i][idx:])
                    paths[i] = a
                    del paths[j]
                    break


    print(' '.join(str(x+1) for x in p[:-1]))



main()