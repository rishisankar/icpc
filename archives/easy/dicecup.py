l = input().split(' ')
l1 = int(l[0])
l2 = int(l[1])
a = min(l1,l2)
b = max(l1,l2)
for i in range(a+1,b+2):
    print(i)