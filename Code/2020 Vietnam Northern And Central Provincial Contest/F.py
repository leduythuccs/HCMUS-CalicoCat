

#f[i] = f[i - 1] + g[i // 2] + sum(j = 1 -> i - 1) g[i - j] 
#g[i] = 9 * pow(10, (i - 1) // 2)
P = [0] * 100
g = [0] * 100
f = [0] * 100
f[0] = 2
f[1] = 11
P[0] = 1
for i in range(1, 40):
    P[i] = P[i - 1] * 10
for i in range(1, 40):
    g[i] = 9 * P[(i - 1) // 2]
for i in range(2, 40):
    f[i] = f[i - 1]
    for j in range(0, i):
        f[i] += g[i - j]
# print(f)
# print(g)
t = int(input())
for i in range(t):
    n = int(input())
    print(f[n])
