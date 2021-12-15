n = int(input())
print(2+max([i+x for i,x in enumerate(sorted(list(map(int, input().split(' '))), reverse=True))]))