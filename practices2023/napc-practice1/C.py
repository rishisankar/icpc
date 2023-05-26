from math import sqrt

def getRange(s, ch):
    l = []
    for i,c in enumerate(s):
        if c == ch:
            if len(l) == 0:
                l.append([i,i])
            elif l[-1][1] == i-1:
                l[-1][1] = i
            else:
                l.append([i,i])
    return l

r,c = map(int,input().split())
lines = []
for i in range(r):
    lines.append(input())
if r == 1:
    print(round(eval(lines[0])))
    exit(0)

rund = getRange(lines[0], "_")
rf = getRange(lines[1], '=')

ranges = []
while (len(rund) > 0 or len(rf) > 0):
    if len(rf) == 0:
        ranges.append(rund[-1])
        rund.pop()
    elif len(rund) == 0:
        ranges.append(rf[-1])
        rf.pop()
    elif rf[-1][1] > rund[-1][1]:
        ranges.append(rf[-1])
        rf.pop()
    else:
        ranges.append(rund[-1])
        rund.pop()
    
# print(rund)
for r in ranges:
    if lines[0][r[0]] == "_":
        lines[1] = lines[1][0:r[0]-2] + str(round(sqrt(eval(lines[1][r[0]:r[1]+1])))) + lines[1][r[1]+1:]
    else:
        lines[1] = lines[1][0:r[0]] + str(round( eval(lines[0][r[0]:r[1]+1]) / eval(lines[2][r[0]:r[1]+1]) )) + lines[1][r[1]+1:] 
print(round(eval(lines[1])))