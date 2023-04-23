def long_division(x,y,p):
  A = x // y
  R = x % y
  ans = str(A) + "."
  for _ in range(p):
    R *= 10
    ans += str(R//y)
    R = R % y
  return ans

n = int(input())
v = []
for i in range(n):
  v.append(tuple(map(int,input().split())))
v.sort()
vv = []
for i in range(n):
  if i == 0 or v[i][0] != v[i-1][0]:
    vv.append([v[i][0], [v[i][1], v[i][1]]])
  else:
    vv[-1][1][1] = v[i][1]
n = len(vv)
xb = (1000000000000000000,1)
for i in range(n-1):
  xi = vv[i][0]
  yi = vv[i][1][1]
  xj = vv[i+1][0]
  yj = vv[i+1][1][0]
  XD = yi*xj-yj*xi
  if XD != 0:
    X = (yi*xj*xj-yj*xi*xi, XD)
    A = (yi*X[1], xi*(xi*X[1]-X[0]))
    if X[1] == 0 or A[1] == 0:
      continue
    if X[1] < 0:
      X = (-X[0], -X[1])
    if A[1] < 0:
      A = (-A[0], -A[1])
    if X[0]>=X[1] and A[0] < 0:
      if X[0]*xb[1] <= xb[0]*X[1]:
        xb = X
assert(xb[0] < 1000000000000000000*xb[1])
print(long_division(xb[0],xb[1],25))
