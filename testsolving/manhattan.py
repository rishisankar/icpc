import functools
from math import comb

n,b = map(int, input().split(" "))

total = 0

cache = {}

def paths(x, y):
    if (x,y) in cache:
        return cache[(x,y)]
    count = comb(b+x+y,y) * comb(b+x+y,x)
    for xp in range(x+1):
        for yp in range(y+1):
            if xp == x and yp == y:
                continue
            count -= paths(xp,yp) * (comb((x-xp)+(y-yp), x-xp)**2)
    cache[(x,y)] = count
    return count

print(paths(100, 30))