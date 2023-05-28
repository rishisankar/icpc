import sys

d = {}
dz = []

g = {}
gz = []

cn = 0
bn = -1

rets = set()

up_edges = []

lz = {}
  
  
for line in sys.stdin.readlines():
  x = line.strip().split()
  if len(x) == 0: continue
  if x[0] == "P":
    d[x[1]] = len(d)
    dz.append(x[1])
  elif x[0] == "L":
    lz[x[1]] = len(lz)
  elif x[0] == "SET":
    
  elif x[0] == "N":
    cn = len(g)
    g[x[1]] = len(g)
    gz.append(x[1])
  elif x[0] == "BUG":
    bn = cn
  elif x[0] == "RET":
    rets.add(cn)
  elif x[0] == "CE":
    up_edges.append((cn, x[2], " ".join(x[4:])))
  elif x[0] == "UE":
    up_edges.append((cn, x[2], "1 == 1"))

vals = set()
for i in range(-30,31):
  vals.add(i)

n = len(gz)
adj = []
for i in range(n): adj.append([])
for edge in up_edges:
  adj[edge[0]].append((g[edge[1]], edge[2]))

vals1 = vals.copy()
vals2 = vals.copy()
if len(dz) > 2:
  vals3 = vals.copy()
else:
  vals3 = set()
  vals3.add(1)
if len(dz) > 3:
  vals4 = vals.copy()
else:
  vals4 = set()
  vals4.add(1)

for a in vals1:
  for b in vals2:
    for c in vals3:
      for d in vals4:
        varmap = {}
        for i,var in enumerate(dz):
          if i == 0:
            varmap[var] = a
          elif i == 1:
            varmap[var] = b
          elif i == 2:
            varmap[var] = c
          else:
            varmap[var] = d
        s = [0]
        vis = [False] * n
        vis[0] = True
        while (len(s) > 0) :
          t = s.pop()
          if t == bn:
            for dest, expr in varmap.items():
              print(dest, ":=", expr)
            exit(0)
          for edge in adj[t]:
            const = edge[1]
            for dest, expr in varmap.items():
              const = const.replace(" " + dest +  " ", " " + str(expr) + " ")
            if (eval(const) == True):
              if vis[edge[0]] != True:
                s.append(edge[0])
                vis[edge[0]] = True


print("No solution")