def amtDigits(x):
  ans = 0
  ct = 1
  pw = 10
  while True:
    if (x >= pw):
      ans += (pw//10*9)*ct
      pw *= 10
      ct+=1
    else:
      break
  pw//=10
  ans += (x-pw+1)*ct
  return ans

lo = 1
hi = int(1e18)
thres = int(1e18) + 5
best = hi # stores smallest number with amtDigits > thres
while lo<=hi:
  mid = lo+(hi-lo)//2
  x = amtDigits(mid)
  if x > thres:
    best = mid
    hi = mid-1
  else:
    lo = mid+1
print(best)

print(amtDigits(100))