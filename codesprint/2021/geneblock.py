t = int(input())
for te in range(t):
  n = int(input())
  ct = 0
  found = False
  while n >= 0:
    n -= 7
    ct += 1
    if n%10 == 0:
      print(ct)
      found = True
      break
  if not found:
    print(-1)
