t = int(input())
for tests in range(t):
  n,k,x = map(int, input().split(" "))
  s = input()
  ast = []
  for i in range(len(s)):
    if s[i] == '*':
      if i == 0 or s[i-1] == 'a':
        ast.append(1)
      else:
        ast[-1] += 1

  i = len(ast) - 1
  prod = [1] * (len(ast)+1)
  while i >= 0:
    prod[i] = prod[i+1] * ((ast[i]*k)+1)
    i -= 1
  i = len(ast) - 1
  while i >= 0:
    if x <= prod[i]:
      break
    i -= 1

  res = []
  for j in range(len(ast)):
    if j >= i:
      val = ((x-1) // prod[j+1]) + 1
      st = "b" * (val-1)
      res.append(st)
      x -= (val-1) * prod[j+1]
    else:
      res.append("")

  prev = "a"
  asti = 0
  rst = ""
  for i in range(len(s)):
    if s[i] == "*" and prev == "a":
      rst += res[asti]
      asti += 1
    elif s[i] == "a":
      rst += "a"
    prev = s[i]
  print(rst)