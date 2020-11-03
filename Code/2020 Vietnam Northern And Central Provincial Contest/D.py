def nxt(n):
    return int(n) + int(n[::-1])
t = int(input())
for i in range(t):
    n = str(input())
    if (int(n) % 7 == 0):
        print(n)
        continue
    for j in range(1000):
        n = nxt(n)
        if (n % 7 == 0):
            print(n)
            n = -1
            break
        n = str(n)
    if (n != -1):
        print(-1)
            