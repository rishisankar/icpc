n = int(input())
l = list(map(int, input().split(" ")))
e = [-1]*n
s = 0
for i, c in enumerate(l):
    s = (s+c)%n
    if s == 0:
        print(i+1)
        print(' '.join(map(str,range(1, i+2))))
        exit(0)
    elif e[s] != -1:
        print(i-e[s])
        print(' '.join(map(str,range(e[s]+2, i+2))))
        exit(0)
    else:
        e[s]=i
