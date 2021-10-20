def n(x):
  return 0 if x == 1 else 1

def f(x):
  a1,a0,b1,b0 = map(int, x)
  # return (n(a1) & n(b1) & (n(b0) | a0))  | (a1 & (a0 | n(b1) | n(b0)))
  # return (a0 & a1) | (a0 & n(b1)) | (a1 & n(b1)) | (n(b0) & n(b1)) | (n(b0) & a1)
  return (a1 & n(b1)) | (a1 & a0) | (n(b1) & n(b0)) | (a1 & n(b0))
  # return (n(a1) & a0 & n(b1)) | (a1 & a0) | (a1 & b1 & n(b0))

s=""
for i in range(16):
  j = f('{0:04b}'.format(i))
  s+=str(j)
  print(j, end="")
print()
if s != "1000110011101111":
  print("fail")
else:
  print("correct")
