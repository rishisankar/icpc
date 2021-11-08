import sys

for line in sys.stdin:
  x = line.lower()
  if "problem" in x:
    print("yes")
  else:
    print("no")