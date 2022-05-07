s = input()
st = set()
for i in s:
  st.add(i)
if len(s) != len(st):
  print(0)
else:
  print(1)