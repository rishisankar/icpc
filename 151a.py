from math import cos, sin, exp

def f(x):
  return -x*x*x - cos(x)
def df(x):
  return -3*x*x + sin(x)

def newt(p):
  return p - f(p)/df(p)


def h(x):
  return exp(x) + 2**(-x) + 2 * cos(x) - 6

def sec(p0, p1):
  return p1 - h(p1) * ( (p1 - p0) / (h(p1) - h(p0)) )

cur = (1.5, 1.75)
eps = 10e-5
while abs(h(cur[1])) > eps:
  print(cur[0], abs(h(cur[0])))
  p2 = sec(*cur)
  cur = (cur[1], p2)
print(cur[0], abs(h(cur[0])))
print(cur[1], abs(h(cur[1])))


