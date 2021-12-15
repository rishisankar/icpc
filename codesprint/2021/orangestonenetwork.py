res = []

def run(k,p,a):
  if a != 1:
    for ad in adj[k]:
      if ad[0] == p:
        continue
      swap(ad[0],0,k,ad[1])
    res.append(k+1)
    for i,ad in enumerate(adj[k]):
      adj[k][i] = ad[0],(int(not ad[1])),ad[2]
      adj[ad[0]][ad[2]] = k,(int(not ad[1])),i
  for ad in adj[k]:
    if ad[0] == p:
      continue
    run(ad[0],k,ad[1])

def swap(k,v,p,a):
  if v == a:
    return
  for ad in adj[k]:
    if ad[0] == p:
      continue
    swap(ad[0],a,k,ad[1])
  res.append(k+1)
  for i,ad in enumerate(adj[k]):
    adj[k][i] = ad[0],(int(not ad[1]))
    adj[ad[0]][ad[2]] = k,(int(not ad[1])),i

n = int(input())
adj = []
for i in range(n):
  adj.append([])
for i in range(n-1):
  i,j,s = map(int, input().split(" "))
  i-=1
  j-=1
  i_n = len(adj[i])
  j_n = len(adj[j])
  adj[i].append((j,s,j_n))
  adj[j].append((i,s,i_n))

s = []
run(0,-1,1)

print(len(res))
for i in res:
  print(i)