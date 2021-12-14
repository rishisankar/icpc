from math import gcd

t = int(input())
thres = 10**18

for i in range(t):
  n = int(input())
  v = list(map(int, input().split(" ")))
  d = v[0]
  failed = False
  for i in range(0, n, 2):
    d = gcd(d, v[i])
    if (d > thres):
      failed = True
      break
  if not failed:
    for i in range(1, n, 2):
      if v[i] % d == 0:
        failed = True
        break
  if not failed:
    print(d)
    continue
  d = v[1]
  failed = False
  for i in range(1, n, 2):
    d = gcd(d, v[i])
    if (d > thres):
      failed = True
      break
  if not failed:
    for i in range(0, n, 2):
      if v[i] % d == 0:
        failed = True
        break
  if not failed:
    print(d)
    continue
  print(0)
