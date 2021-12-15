tests = int(input())
for i in range(tests):
    n = int(input())
    s = set()
    for j in range(n):
        st = input()
        s.add(st)
    print(len(s))