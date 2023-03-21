from math import comb
def cat(n):
    return comb(2*n,n)//(n+1)
n = int(input())
print(cat(n+1))