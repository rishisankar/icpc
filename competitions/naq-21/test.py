import random
print(1000)
s = ""
for i in range(1000):
  s += str(random.randint(1, 1000000)) + " "
print(s)