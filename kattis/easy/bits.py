t = int(input())
for i in range(t):
  r = ""
  ctt = 0
  x = input()
  for a in x:
    r += a
    y = bin(int(r))
    ct = 0
    for s in y:
      if s == "1":
        ct += 1
    ctt = max(ctt, ct)
  print(ctt)
