ins = input()
ss = ins.split("+")
plsz = len(ss)-1
vals = set()
x = 1 << plsz
for i in range(x):
  add = [int(ss[0])]
  for j in range(len(ss)-1):
    if ((i >> j) & 1) == 1:
      add.append(int(ss[j+1]))
    else:
      add[len(add)-1] = int(str(add[len(add)-1]) + str(ss[j+1]))
  vv = 0
  for ii in add:
    vv += ii
  vals.add(vv)
print(len(vals))

