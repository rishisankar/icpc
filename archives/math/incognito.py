t = int(input())
for tests in range(t):
    n = int(input())
    c = {}
    for i in range(n):
        s = input().split(" ")
        s1 = s[0]
        s2 = s[1]
        if s2 in c:
            c[s2] += 1
        else:
            c[s2] = 1
    
    total = 1

    for key in c:
        total *= (c[key] + 1)
    
    print(total-1)