import random
from math import comb
import numpy as np

# returns 1 with probability 12/13, 0 with probability 1/13
def query():
    return 0 if random.randrange(0,13) == 0 else 1

num_samples = 10000000
fails = 0
time = 0
times = []
k = 5


"""
all the last 5
(returns True, val), or False, -1
"""
def check_history(hist):
    if len(hist) < 5:
        return False,-1
    if sum([hist[-i] != hist[-i-1] for i in range(1,k)]) == 0:
        return True,hist[-1]
    if len(hist) >= 10:
        ct0 = 0
        ct1 = 0
        for x in hist:
            if x==True:
                ct1+=1
            else:
                ct0+=1
        if ct0 > ct1:
            return True,0
        else:
            return True,1
    return False,-1


for s in range(num_samples):
    x=[]
    t = 0
    while not check_history(x)[0]:
        x.append(query())
        t += 1
    if check_history(x)[1] == 0:
        fails += 1
    time += t
    times.append(t)
print(fails/num_samples)
print(time/num_samples)
print(np.std(times))


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


def get_stats(case_success):
    print("Probability of success", case_success)
    success_over_248 = 0
    for i in range(248,251):
        success_over_248 += comb(250,i) * case_success**i * (1-case_success)**(250-i)
    print("Probability of passing a case", success_over_248)
    print("Probability of AC with 30 cases", success_over_248**30)