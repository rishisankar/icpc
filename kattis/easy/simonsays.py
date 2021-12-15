n = int(input())
for tests in range(n):
    line = input()
    if line.startswith("Simon says"):
        print(line[10:])