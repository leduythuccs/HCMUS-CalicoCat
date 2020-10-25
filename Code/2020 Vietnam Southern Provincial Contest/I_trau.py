import re
P = input().strip()
P = P.replace('*', '.*')
# print(P)
S = input().strip()
n = len(S)
S = S + S
res = 0
for i in range(0, n):
    tmp =  re.findall(P, S[i : i + n])
    # print(tmp)
    for match in tmp:
        if len(match) == n:
            res += 1
            break
print(res)