
n = int(input())
ct = 0
for i in range(n):
  s = input().lower()
  if "pink" in s or "rose" in s:
    ct += 1
if ct == 0:
  print("I must watch Star Wars with my daughter")
else:
  print(ct)
