line = input().split(" ")
a = int(line[0])
b = int(line[1])
c = int(line[2])

if a+b == c:
    print(str(a) + "+" + str(b) + "=" + str(c))
elif a-b == c:
    print(str(a) + "-" + str(b) + "=" + str(c))
elif a*b == c:
    print(str(a) + "*" + str(b) + "=" + str(c))
elif a/b == c:
    print(str(a) + "/" + str(b) + "=" + str(c))
elif a == b+c:
    print(str(a) + "=" + str(b) + "+" + str(c))
elif a == b-c:
    print(str(a) + "=" + str(b) + "-" + str(c))
elif a == b*c:
    print(str(a) + "=" + str(b) + "*" + str(c))
elif a == b/c:
    print(str(a) + "=" + str(b) + "/" + str(c))