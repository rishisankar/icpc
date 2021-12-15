n = int(input())
sum = 0
for i in range(n):
    line = input()
    base = int(line[:-1])
    exp = int(line[-1])
    sum += base ** exp
print(sum)