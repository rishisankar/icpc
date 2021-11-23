from math import cos, sin, exp, log, pi, sqrt

def newt(p, fn, dfn):
  return p - fn(p)/dfn(p)

def sec(p0, p1, fn):
  return p1 - fn(p1) * ( (p1 - p0) / (fn(p1) - fn(p0)) )

def bwd(f, x0, h):
  return (f(x0) - f(x0 - h)) / h

def f(x):
  return sin(x)
