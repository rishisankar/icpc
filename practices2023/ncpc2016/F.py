facts = [1]
for i in range(1,300000):
    facts.append(facts[-1]*i)
print(facts[4])