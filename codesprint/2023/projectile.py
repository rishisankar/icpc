n = int(input())
v = []
for i in range(n):
  v.append(tuple(map(float,input().split())))
v.sort()
vv = []
for i in range(n):
  if i == 0 or v[i][0] != v[i-1][0]:
    vv.append([v[i][0], [v[i][1], v[i][1]]])
  else:
    vv[-1][1][1] = v[i][1]
n = len(vv)
xb = 1000000000000000000.0
for i in range(n-1):
  xi = vv[i][0]
  yi = vv[i][1][1]
  xj = vv[i+1][0]
  yj = vv[i+1][1][0]
  if yi*xj-yj*xi != 0:
    X = (yi*xj*xj-yj*xi*xi)/(yi*xj-yj*xi)
    A = yi/xi/(xi-X)
    if X>=1 and A < 0:
      xb = min(xb,X)
print("{:.15f}".format(xb))