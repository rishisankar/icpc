"""

only important part: L := max Li (Li = # shirts washed in ith washing cycle)

1) if L < i, then position must still be i
2) if L >= i then uniformly random 1...L

P(L<i) = P(Li<i) ^ k 
P(Li<i) = (i-1)/n

P(L>=i) = 1-P(L<i)
Expected position: (L+1)/2 since each thing 1..L equally likely


P(L=j) = P(L<j+1) - P(L<j) = (j/n)^k -((j-1) / n)^k
"""


n,i,k,z=*map(int,input().split()),0
for j in range(i,n+1):z+=(j+1)/2*((j/n)**k-((j-1)/n)**k)
print(((i-1)/n)**k*i+z)

