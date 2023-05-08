import random
from math import comb

# returns 1 with probability 12/13, 0 with probability 1/13
def query():
    return 0 if random.randrange(0,13) == 0 else 1

num_samples = 10000000
fails = 0
time = 0
k = 5
for s in range(num_samples):
    x=[-2]
    for i in range(k-1):
        x.append(-1)
    t = 0
    while sum([x[-i] != x[-i-1] for i in range(1,k)]) != 0:
        x.append(query())
        t += 1
    if x[-1] == 0:
        fails += 1
    time += t
print(fails/num_samples)
print(time/num_samples)


def success_rate(query_failure):
    success_in_approach = (1-query_failure)**60
    success_over_250 = success_in_approach**250
    print(success_in_approach)
    print(success_over_250)
    success_over_248 = 0
    for i in range(248,251):
        success_over_248 += comb(250,i) * success_in_approach**i * (1-success_in_approach)**(250-i)
    print(success_over_248)
success_rate(fails/num_samples)