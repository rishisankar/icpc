from itertools import permutations
from collections import deque
from math import sqrt
import sys

N,d,s,t,fmin,fmax = map(int, input().split(" "))

def distance(cross:bool, x1, x2):
    if cross:
        return sqrt(s*s + ((x1-x2)*d)**2)
    else:
        return d

res = 0

# def rec(index, left: bool, perm, dist):
#     global res
#     if index == len(perm) - 1:
#         dist *= 2
#         dist += s
#         dist += (index+2)*2*t
#         dist = (L - dist)/2
#         if dist >= fmin and dist <= fmax:
#             res += 1
#         # print(dist, perm)
#         return

#     nex = perm[index+1]

#     if abs(perm[index] - nex) == 1:
#         newdist = distance(False, perm[index], nex)
#         rec(index+1, left, perm, dist + newdist)
#     newdist2 = distance(True, perm[index], nex)
#     rec(index+1, not left, perm, dist + newdist2)

Ls = []
for line in sys.stdin:
    L = int(line)
    Ls.append([L,0])

for holes in range(N-1):
    for perm in permutations(range(1,N-1), holes):
        perm = perm + (N-1,)
        stack = deque()
        if perm[0] == 1:
            stack.append((0, True, distance(False, 0, 1)))
            # rec(0, True, perm, distance(False, 0, 1))
        stack.append((0, False, distance(True, 0, perm[0])))
        # rec(0, False, perm, distance(True, 0, perm[0]))
        while len(stack) != 0:
            index, left, dist = stack.pop()
            if index == len(perm) - 1:
                dist *= 2
                dist += s
                dist += (index+2)*2*t
                for lis in Ls:
                    L = lis[0]
                    tmp = (L - dist)/2
                    if tmp >= fmin and tmp <= fmax:
                        lis[1] += 1
                continue

            nex = perm[index+1]

            if abs(perm[index] - nex) == 1:
                newdist = distance(False, perm[index], nex)
                stack.append((index+1, left, dist + newdist))
            newdist2 = distance(True, perm[index], nex)
            stack.append((index+1, not left, dist + newdist2))

for lis in Ls:
    print(lis[1])