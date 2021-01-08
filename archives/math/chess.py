# doesn't work!

black_diagonal=["A1",'B2','C3','D4','E5','F6','G7','H8']
white_diagonal=['A8','B7','C6','D5','E4','F3','G2','H1']
black_counts = {'A':1,'B':2,'C':3,'D':4,'E':5,'F':6,'G':7,'H':8}
white_counts = {'A':8,'B':7,'C':6,'D':5,'E':4,'F':3,'G':2,'H':1}

def black(piece):
    return (black_counts[piece[0]] + int(piece[1])) % 2 == 0

def getToDiagonal(piece):
    if black(piece):
        return black_diagonal[(black_counts[piece[0]] + int(piece[1]))//2 - 1]
    else:
        return white_diagonal[7-((white_counts[piece[0]] + int(piece[1]))//2 - 1)]

t = int(input())

for tests in range(t):
    line = input().split(' ')
    start = line[0] + line[1]
    end = line[2] + line[3]

    if black(start) != black(end):
        print("Impossible")
    elif start == end:
        print("0 " + line[0] + " " + line[1])
    else:
        l = []
        l.append(start)
        tmp = getToDiagonal(start)
        if tmp != start:
            l.append(tmp)
        tmp2 = getToDiagonal(end)
        if tmp2 != tmp:
            l.append(tmp2)
        if tmp2 != end:
            l.append(end)
        out = str(len(l))
        for st in l:
            out += " "
            out += st[0]
            out += " "
            out += st[1]
        print(out)
