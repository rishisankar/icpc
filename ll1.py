S = "A"
# G = {
#   "A": ["ACB", "x", "y"],
#   "B": ["zw"],
#   "C": ["CCB", "yz"]
# }

G = {
  "A": ["$", "xyB", "zyC"],
  "B": ["w", "xzB"],
  "C": ["$", "zy"]
}

# G = {
#   "A": ["wxw", "xBC"],
#   "B": ["$", "x"],
#   "C": ["ywA", "$"]
# }

# G = {
#   "A": ["$", "xC"],
#   "B": ["xz"],
#   "C": ["AxC", "xyB", "wzB"]
# }

# G = {
#   "A": ["Cx", "zCA"],
#   "B": ["xyA", "Cz"],
#   "C": ["yBy"]
# }

# G = {
#   "A": ["wB", "yC", "$"],
#   "B": ["wz", "$", "zA"],
#   "C": ["xBx", "w"]
# }

# G = {
#   "A": ["wyC", "xCC", "y"],
#   "B": ["BB", "x"],
#   "C": ["$", "AwB", "xC"]
# }

def nullable(x):
  if x == "":
    return True
  if x == "$":
    return True
  elif len(x) > 1:
    for a in x:
      if a.islower():
        return False
    return all([nullable(a) for a in x])
  elif x.islower():
    return False
  else:
    for gr in G[x]:
      if nullable(gr):
        return True
    return False


def first(x):
  if x == "":
    return ["$"]
  if x == "$":
    return []
  elif x[0].islower():
    return [x[0]]
  else:
    res = []
    if nullable(x[0]):
      res.extend(first(x[1:]))
    for gr in G[x[0]]:
      res.extend(first(gr))
    return list(set(res))

def follow_helper():
  f = {}
  adj = {} # A->B means B is a subset of A
  for i in G.keys():
    f[i] = set()
    adj[i] = set()
  f[S].add("$")
  for nt in G.keys():
    for gr in G[nt]:
      for i in range(len(gr)):
        if gr[i].isupper():
          st = set(first(gr[i+1:]))
          if "$" in st:
            st.remove("$")
            adj[gr[i]].add(nt)
          f[gr[i]].update(st)
  
  for nt in G.keys():
    stack = [nt]
    visited = set()
    visited.add(nt)
    while len(stack) > 0:
      t = stack.pop()
      for y in adj[t]:
        if y in visited:
          continue
        stack.append(y)
        visited.add(y)
    for v in visited:
      for i in f[v]:
        f[nt].add(i)
  return f  

flw = follow_helper()

def follow(x):
  return list(flw[x])

def table():
  tbl = {}
  for nt in G.keys():
    tbl[nt] = {}
  for nt in G.keys():
    for P in G[nt]:
      fst = first(P)
      for i in fst:
        if i != "$" and i.islower():
          if i in tbl[nt]:
            tbl[nt][i].append(P)
          else:
            tbl[nt][i] = [P]
      if nullable(P):
        fw = follow(nt)
        for i in fw:
          if i == "$" or i.islower():
            if i in tbl[nt]:
              tbl[nt][i].append(P)
            else:
              tbl[nt][i] = [P]

  return tbl

def print_table():
  isLL1 = True
  nts = list(G.keys())
  terms = set("$")
  for nt in nts:
    for P in G[nt]:
      for i in P:
        if i != "$" and i.islower():
          terms.add(i)
  terms = list(terms)
  tbl = table()
  for nt in nts:
    for t in terms:
      x = []
      if t in tbl[nt]:
        x = list(set(tbl[nt][t]))
        if len(x) > 1:
          isLL1 = False
      print(f"({nt}, {t}): {x}")
    print()
  isLL1 = "" if isLL1 else "not "
  print(f"The grammar is {isLL1}LL(1)")
