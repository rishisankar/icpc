n = int(input())
x = {}
for i in range(n):
  l = input()
  if l in x:
    x[l] += 1
  else:
    x[l] = 1
y = {}
for i in range(n):
  l = input()
  if l in y:
    y[l] += 1
  else:
    y[l] = 1
ct = 0
for k in y:
  if k in x:
    ct += min(y[k], x[k])
print(ct)
