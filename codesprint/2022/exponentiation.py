from math import lcm

def period(x):
  nd = len(str(x))
  mod = 10**nd
  st = x
  for i in range(1,mod+1):
    st = (st*x)%mod
    if st == x:
      return i
  return -1

n = int(input())
a = list(map(int, input().split(" ")))
p = []
for i in range(n):
  p.append(period(a[i]))

def solve(ls):
  l = 1
  for x in ls:
    if x == -1:
      return -1
    l = lcm(l, x)
  return 1+l

print(solve(p))
