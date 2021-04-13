s1, s2 = input().split(" ")

def y1t(pt):
    if pt[0] < "f":
        return int(pt[1:]) + (ord("f")-ord(pt[0]))
    else:
        return int(pt[1:])

def y2t(pt):
    if pt[0] > "f":
        return int(pt[1:]) - (ord("f")-ord(pt[0]))
    else:
        return int(pt[1:])

def can_move(src, dest):
    if src == dest:
        return False
    if src[0] == dest[0]:
        return True
    if y1t(src) == y1t(dest):
        return True
    if y2t(src) == y2t(dest):
        return True
    return False

pieces = []
for i in range(6):
    ch = chr(i+ord("a"))
    for j in range(1, 7+i):
        pieces.append(ch + str(j))
    if i != 5:
        ch2 = chr(ord("k")-i)
        for j in range(1, 7+i):
            pieces.append(ch2 + str(j))

ct = 0

for p in pieces:
    if can_move(s1, p) and can_move(p, s2):
        ct += 1

print(ct)