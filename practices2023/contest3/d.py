import sys
n=int(input())
v=[int(x) for x in input().split()]

x=1
mod=1000000000+7
exceeded=False
for i in range(n):
  if(x>100000*(2**65)):
    exceeded=True
  
  if(not exceeded):
    x=x*2
    x=x-v[i]
    if(x<0):
      print("error")
      exit(0)
  else:
    x=(x*2)%mod
    cur=mod
    while(cur<v[i]):
      cur=cur*2
    add=cur-v[i]
    x=(x+add)%mod

print(x)
