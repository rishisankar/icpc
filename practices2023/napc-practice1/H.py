m = 1000000007
T = int(input())
for t in range(T):
  R,C = map(int,input().split())
  x = (18 * pow(6,R+C-2,m) * pow(2,(R-1)*(C-1),m))%m
  print(x)