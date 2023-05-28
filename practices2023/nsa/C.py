p = int(input())
g = int(input())
y = int(input())
C = int(input())
q = int(input())
if(p==0):
  print("INVALID")
  exit(0)
h = pow(g, C, p)
if (pow(g, q, p)*pow(y, h, p))%p == C:
  print("VALID")
else:
  print("INVALID")