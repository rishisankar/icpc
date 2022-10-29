

def neg(D):
  r = ""
  for i in D:
    r += ("1" if i == "0" else "0")
  return r

def a1(D):
  D = [i for i in D]
  for x in range(len(D)):
    i = len(D)-1-x
    if D[i] == "0":
      D[i] = "1"
      return "".join(D)
    else:
      D[i] = "0"
  return "".join(D)

def lshift(D,k ):
  if k >= 12:
    return "0"*12
  else:
    return D[k-12:] + "0"*k

def rshift(D,k ):
  if k >= 12:
    return "0"*12
  else:
    return "0"*k + D[:-k]

def solve(D):
  S = D[0]
  sign_mag = D
  if (S == "1"):
    sign_mag = a1(neg(D))
  lead_zeroes = 8
  if (sign_mag[0] == "1"):
    lead_zeroes = 0
  elif (sign_mag[1] == "1"):
    lead_zeroes = 1
  elif (sign_mag[2] == "1"):
    lead_zeroes = 2
  elif (sign_mag[3] == "1"):
    lead_zeroes = 3
  elif (sign_mag[4] == "1"):
    lead_zeroes = 4
  elif (sign_mag[5] == "1"):
    lead_zeroes = 5
  elif (sign_mag[6] == "1"):
    lead_zeroes = 6
  elif (sign_mag[7] == "1"):
    lead_zeroes = 7
  
  significand = rshift(lshift(sign_mag, lead_zeroes), 8)
  assert significand[:8] == "0"*8
  significand = significand[8:]
  exp = 8 - lead_zeroes
  roundbit = rshift(lshift(sign_mag, lead_zeroes), 7)[-1]

  if roundbit == "1" and significand != "1111":
    significand = a1(significand)
  elif roundbit == "1" and significand == "1111" and exp != 7:
    exp = exp+1
    significand = "1000"
  
  if sign_mag == "1" + "0"*11:
    exp = 7
    significand = "1111"
  
  return S + bin(exp)[2:].zfill(3) + significand

def f2i(x):
  res = 1.0
  if x[0] == "1":
    res *= -1
  exp = (1 << int(x[1:4], 2))
  res *= exp
  res *= int(x[4:], 2)
  return res

for i in range(1 << 12):
  x = bin(i)[2:].zfill(12)
  val = i
  if x[0] == "1":
    x2 = [i for i in x]
    x2[0] = "0"
    x2 = "".join(x2)
    val = int(x2,2) - (1 << 11)
  
  sug = solve(x)
  diff = abs(f2i(sug) - val)
  vsugs = set()

  if diff == 1:
    print("D1", val, x, sug)

  best = diff
  bestsug = sug
  for j in range(1 << 8):
    jsug = bin(j)[2:].zfill(8)
    jdif = abs(f2i(jsug) - val)
    if jdif < best:
      best = jdif
      bestsug = jsug
    if jdif == diff:
      vsugs.add(jsug)
  
  if bestsug != sug:
    print("Diff", val, x, sug, diff, best, bestsug)
  if len(vsugs) > 1 and sug[4] != "1":
    for s in vsugs:
      if s[4] == "1":
        print("Non-1 leading sig", val, x, sug, diff, s, vsugs)
        break

