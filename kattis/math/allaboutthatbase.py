possible = "0123456789abcdefghijklmnopqrstuvwxyz"
baseDict = {char: index for index, char in enumerate(possible)}
intmax = pow(2,32) - 1

def allOnes(num):
    for ch in num:
        if ch != "1":
            return False
    return True

def oneWorks(num1, op, num2, result):
    if allOnes(num1) and allOnes(num2) and allOnes(result):
        n1 = len(num1)
        n2 = len(num2)
        res = len(result)
        if (op == '+' and n1 + n2 == res) or (op == '-' and n1 - n2 == res) or (op == '/' and n1 / n2 == res) or (op == '*' and n1 * n2 == res):
            if n1 >= 1 and n1 <= intmax and n2 >= 1 and n2 <= intmax and res >= 1 and res <= intmax:
                return True
    return False

def lowestBase(num):
    lowestChar = num[0]
    for ch in num:
        if ch > lowestChar:
            lowestChar = ch
    return baseDict[lowestChar] + 1

def lowest(num1, num2, num3):
    return max(lowestBase(num1), lowestBase(num2), lowestBase(num3))


if __name__ == "__main__":
    N = int(input())
    for testcases in range(N):
        line = input().split()
        num1 = line[0]
        op = line[1]
        num2 = line[2]
        result = line[4]

        result_str = ""
        if oneWorks(num1, op, num2, result):
            result_str += "1"

        minBase = lowest(num1, num2, result)

        for base in range(minBase,37):
            n1 = int(num1, base)
            n2 = int(num2, base)
            res = int(result, base)

            if (op == '+' and n1 + n2 == res) or (op == '-' and n1 - n2 == res) or (op == '/' and n1 / n2 == res) or (op == '*' and n1 * n2 == res):
                if n1 >= 1 and n1 <= intmax and n2 >= 1 and n2 <= intmax and res >= 1 and res <= intmax:
                    if base == 36:
                        result_str += "0"
                    else:
                        result_str += possible[base]

        if result_str == "":
            result_str = "invalid"

        print(result_str)
