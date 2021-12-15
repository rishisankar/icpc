n,d = map(int, input().split(" "))
ct = {}
line = input().split(" ")
for i in range(n):
    x = int(line[i])
    div = x // d
    if div in ct:
        ct[div] += 1
    else:
        ct[div] = 1

count = 0
for i in ct.values():
    count += i*(i-1)//2

print(count)
