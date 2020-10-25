a = int(input())
b = int(input())
if (b - a >= 9):
	print(9)
	exit()
a %= 9
b %= 9
if (b < a):
	b += 9
f = 1
for i in range(a, b + 1):
	f = f * i % 9
if (f == 0):
	f = 9
print(f)