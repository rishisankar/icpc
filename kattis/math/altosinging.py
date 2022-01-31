n = int(input())
tones = {}
tonesR = {}
tones["C"] = 0
tones["C#"] = 1
tones["D"] = 2
tones["D#"] = 3
tones["E"] = 4
tones["F"] = 5
tones["F#"] = 6
tones["G"] = 7
tones["G#"] = 8
tones["A"] = 9
tones["A#"] = 10
tones["B"] = 11
for x in tones.keys():
  tonesR[tones[x]] = (len(x) > 1)

def spl(s):
  note = ""
  octv = ""
  if (s[1] == '#'):
    note = s[0:2]
    octv = s[2:]
  else:
    note = s[0:1]
    octv = s[1:]
  return tones[note], int(octv)

def gval2(pl):
    return 12*pl[1] + pl[0]

def gval(s):
    return gval2(spl(s))

def move(tr, pr):
    x = (((pr[0] + tr) % 12) + 12) % 12
    return x

def getNote(val):
    return val%12,val//12


loS, hiS = input().split(" ")
lo = gval(loS)
hi = gval(hiS)
mnv = 10000000000000
mxv = -10000
notes = []
inpnotes = input().split(" ")
for i in range(n):
  notes.append(spl(inpnotes[i]))
  x = gval2(notes[i])
  if x < mnv:
    mnn = notes[i]
    mnv = x
  if x > mxv:
    mxn = notes[i]
    mxv = x

minAcc = 10000000000000
start = [0]*12
for i in range(12):
  transp = i - mnn[0] + 24
  for j in range(n):
    x = move(transp, notes[j])
    if tonesR[x]:
      start[i] += 1
for x in start:
  minAcc = min(minAcc, x)
okt = 0
for x in start:
  if x == minAcc:
    okt += 1

mxVal = mnv + gval(hiS) - mxv
mxValN = getNote(mxVal)
mnValN = spl(loS)

ct = 0

v1 = gval2((mxValN[0], mnValN[1]))
v2 = gval2((mxValN[0], mnValN[1]+1))
strP = gval2(mnValN)
end = v2
if v1>=strP:
  end = v1

vals = []
for i in range(strP, end+1):
  transp = (getNote(i)[0] - mnn[0]) + 24
  cttt = 0
  for j in range(n):
    x = move(transp, notes[j])
    if tonesR[x]:
      cttt += 1
  vals.append(cttt)

minsim = min(vals)

oct1 = getNote(end)[1]
oct2 = mxValN[1]
if (oct1 != oct2):
  resf = 0;
  for x in vals:
    if x == minAcc:
      resf += 1
  resf += (oct2-oct1) * okt
  print(minAcc,resf)
else:
  resf = 0
  for x in vals:
    if x == minsim:
      resf += 1
  print(minsim, resf)
