from math import cos, sin, exp, log, pi

def newt(p, fn, dfn):
  return p - fn(p)/dfn(p)

def sec(p0, p1, fn):
  return p1 - fn(p1) * ( (p1 - p0) / (fn(p1) - fn(p0)) )


def h(x):
  return exp(x) + 2**(-x) + 2 * cos(x) - 6



# cur = (1.5, 1.75)
# eps = 10e-5
# while abs(h(cur[1])) > eps:
#   print(cur[0], abs(h(cur[0])))
#   p2 = sec(*cur)
#   cur = (cur[1], p2)
# print(cur[0], abs(h(cur[0])))
# print(cur[1], abs(h(cur[1])))

def P(x):
  res = -log(2)*(x-1)*(x-3) + 1/2 * log(3) * (x-1) * (x-2)
  print("ans", res)
  print("abs", abs(res - log(x)))
  print("rel", abs((log(x)-res)/res))

def f(x):
  return sin(pi * x)

pts = [(0, 179323), (10, 203302), (20, 226542), (30, 249633), (40, 281422), (50, 308746)]

v = 0
for i in range(6):
  a = pts[i][1]
  for j in range(6):
    if i == j:
      continue
    a *= (60 - pts[j][0])
  for j in range(6):
    if i == j:
      continue
    a /= (pts[i][0] - pts[j][0])
  v += a
print(v)


a0 = -0.29004996
a1 = -0.56079734
a2 = -0.81401972