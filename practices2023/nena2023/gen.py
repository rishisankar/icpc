x = 1
ss = ""
for i in range(1,301):
  ss += f"pmap[{i-1}] = \"{x}\"; "
  x*=2
print(ss)
