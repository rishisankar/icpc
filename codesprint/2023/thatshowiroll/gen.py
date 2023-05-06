z = ["l1","l2","l3","l4","l5","l6"]
for x in z:
    s = "int y = "
    for y in z:
        if x != y:
            s += f"pfx[{x}][{y}] + "
    print(s)