def convert(word):
  prev = "#"
  s = ""
  for c in word:
    if c != prev:
      s += c
    prev = c
  if len(s) <= 2:
    return s
  u = s[0]
  for i in range(1,len(s)-1):
    if not (s[i] == 'a' or s[i] == 'e' or s[i] == 'i' or s[i] == 'o' or s[i] == 'u'):
      u += s[i]
  u += s[-1]
  return u
  

n = int(input())
l = input().split(" ")
assert len(l) == n

for word in l:
  print(convert(word), end=" ")
print()