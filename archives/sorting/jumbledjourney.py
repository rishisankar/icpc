# doesn't work :(

n = int(input())
inp = []
for i in range(n):
  x = map(int, input().split(" "))
  inp.append(list(x))

for i in range(n):
  assert inp[i][i] == 0

oup = []
for i in range(n):
  oup.append([-1] * n)

levels = []
taken = [False]*n
ct = 0
while ct < n:
  lvl = []
  for j in range(n):
    if taken[j]:
      continue
    success = True
    for i in range(n):
      if i == j or taken[i]:
        continue
      if inp[i][j] != -1:
        success = False
        break
    if success:
      lvl.append(j)
  for i in lvl:
    taken[i] = True
    ct += 1
  levels.append(lvl)
# assert ct == n

counts = []
for i in range(n):
  counts.append([0] * n)
for i in range(len(levels) - 1):
  for u in levels[i]:
    for v in levels[i+1]:
      if inp[u][v] != -1:
        counts[u][v] += 1
        oup[u][v] = inp[u][v]
for sep in range(2, len(levels)):
  for st in range(len(levels) - sep):
    for u in levels[st]:
      for v in levels[st+sep]:
        if inp[u][v] == -1:
          continue
        tot = 0
        pts = 0
        for w in range(n):
          if w == u or w == v:
            continue
          if oup[w][v] != -1:
            if counts[u][w] > 0:
              tot += counts[u][w] * (oup[w][v] + inp[u][w])
              pts += counts[u][w]
        goal = inp[u][v]
        if goal * pts != tot:
          pts += 1
          new = pts * goal - tot
          oup[u][v] = new
        counts[u][v] = pts
#for i in range(n):
#  for j in range(n):
#    assert oup[i][j] != 0 and oup[i][j] >= -1
for i in range(n):
  print(' '.join(map(str,oup[i])))