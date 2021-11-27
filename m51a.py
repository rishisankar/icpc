def A(x,y):
  if x=="1" and y=="1":
    return "1"
  else:
    return "0"

def O(x,y):
  if x=="1" or y=="1":
    return "1"
  else:
    return "0"

def N(x):
  if x == "1":
    return "0"
  else:
    return "1"

def XOR(x,y):
  if x == "1" and y == "0":
    return "1"
  elif x == "0" and y == "1":
    return "1"
  else:
    return "0"

# for i in range(16):
#   bs = '{:04b}'.format(i)
#   y1 = bs[0]
#   y0 = bs[1]
#   x1 = bs[2]
#   x0 = bs[3]

#   y1n = O( A(y1, N(A(  N(y0), A(  N(y1), x1  )   ))) ,  A(N(y1), O(y0, N(x0)))   )
#   y0n = XOR(y0,  O( A(N(x1), N(y0) ), A(N(y1), x0)   )   )
#   z = A(N(y1),N(y0))
#   print (bs, y1n, y0n, z)


for i in range(8):
  bs = '{:03b}'.format(i)
  q2 = bs[0]
  q1 = bs[1]
  q0 = bs[2]
  t2 = O(N(XOR(q1,q2)), q0)
  t1 = O(q1,q0)
  t0 = O(XOR(q1,q2),q0)
  print(t2,t1,t0)