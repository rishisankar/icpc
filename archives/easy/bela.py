dom_value = {"A":11,"K":4,"Q":3,"J":20,"T":10,"9":14,"8":0,"7":0}
nondom_value = {"A":11,"K":4,"Q":3,"J":2,"T":10,"9":0,"8":0,"7":0}

line = input().split(' ')
n = int(line[0])
suit = line[1]
sum = 0
for i in range(4*n):
    l = input()
    if l[1] == suit:
        sum += dom_value[l[0]]
    else:
        sum += nondom_value[l[0]]
print(sum)
