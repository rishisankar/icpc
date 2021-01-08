n = int(input())
l = []

for i in range(n):
    num = float(input().split(" ")[1])
    l.append(num)

l.sort()
l.reverse()

res = 0.0

for i in range(len(l)):
    res += l[i]*(i+1)

print(res)
