s = input()
arr = list(map(int, input().split()))
d = [0 for i in range(len(arr))]
p = [0 for i in range(len(arr))]
last = 0
for i in range(len(arr)):
    best = -1
    for j in range(i):
        if arr[i] > arr[j] and (best == -1 or d[j] > d[best]):
            best = j
    if best > -1:
        d[i] = d[best] + 1
        p[i] = best
        if d[i] > d[last]:
            last = i
    else:
        d[i] = 1
        p[i] = -1
ans = []
i = last
while i > -1:
    ans.append(arr[i])
    i = p[i]
print(d[last])
print(' '.join(map(str, reversed(ans))))
