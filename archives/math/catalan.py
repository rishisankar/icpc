f = [1]
for i in range(10000):
    f.append(f[i]*(i+1))
n = int(input())
for i in range(n):
    x = int(input())
    print(f[2*x]//(f[x]*f[x+1]))