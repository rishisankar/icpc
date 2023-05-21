from math import gcd
for k in range(1,10):
  ct = 0
  for i in range(1,k+1):
    for j in range(1,k+1):
      if (gcd(i,j) == 1):
        ct += 1
  print(k,ct)