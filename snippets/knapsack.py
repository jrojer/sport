N, W = map(int, input().split())
weight = [0]
value = [0]
weight.extend(map(int, input().split()))
value.extend(map(int, input().split()))
d = [[0 for i in range(W+1)] for i in range(N+1)]
for i in range(1, N+1):
    for w in range(1, W+1):
        if weight[i] <= w:
            d[i][w] = max(d[i-1][w-weight[i]] + value[i], d[i-1][w])
        else:
            d[i][w] = d[i-1][w]
i = N
w = W
ans = []
while i >= 0 and w >= 0 and d[i][w] > 0:
    if d[i-1][w] == d[i][w]:
        i = i - 1
    else:
        ans.append(i)
        w = w - weight[i]
        i = i - 1
print(len(ans))
print(' '.join(map(str,sorted(ans))))
