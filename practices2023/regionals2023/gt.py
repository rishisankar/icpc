m = 31848
k = 84
ct = 0
for i in range(0,m+1):
    if i&k == k:
        ct += 1
print(ct)