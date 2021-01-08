# doesnt work !

def permute(chars):
    if len(chars) == 1:
        return [chars]
    res = []
    for i in range(len(chars)):
        for permutation in permute(chars[:i] + chars[i+1:]):
            res.append([chars[i]] + permutation)
    return res

if __name__ == "__main__":

    charset = set()
    add = []
    n = int(input())
    for i in range(n):
        line = input()
        if i == n-1:
            res = line
        else:
            add.append(line)

        for ch in line:
            charset.add(ch)

    for i in range(10 - len(charset)):
        charset.add(str(i))

    permutations = permute(list(charset))

    count = 0

    for perm in permutations:
        lookup = {x:y for y,x in enumerate(perm)}
        total = 0
        for word in add:
            wordval = 0
            for i in range(len(word)):
                wordval += (10**(9-i))*lookup[word[i]]
            total += wordval
        
        wordval = 0
        for i in range(len(res)):
            wordval += (10**(9-i))*lookup[res[i]]
        
        if total == wordval:
            count += 1
    
    print(count)

