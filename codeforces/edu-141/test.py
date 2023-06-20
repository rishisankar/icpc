x = 100000
y=x
ct = 1
for i in range(2,y+1):
  j = i-1
  if 1+(x-1)//i != 1+(x-1)//j: ct += 1
print(ct)