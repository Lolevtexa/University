import os
import matplotlib.pyplot as plt

ss = [
    "checkingHeight",
    "checkingInsert",
    "checkingRemove",
]

for s in ss:
    path = "results/" + s

    files = os.listdir(path)

    x, y, t = [], [], []

    for file in files:
        f = open(path + "/" + file, "r")

        l = [[float(i) for i in line.split()] for line in f.read().splitlines()]
        x.append(l[0])
        y.append(l[1])
        t.append(file)

    c = ['b', 'r', 'y']
    for i in range(len(x)):
        plt.plot(x[i], y[i], c[i] + ".", markersize=5)

    plt.xlabel("array size")

    if s == "checkingHeight":
        plt.ylabel("height of tree")
    else:
        plt.ylabel("time (s)")
    
    plt.savefig("png/" + s + ".png")
    plt.clf()

    
    print(s)
    if s == "checkingHeight":
        m0, m1, m2 = 0, 0, 0
        for i in range(len(x[0])):
            m0 += y[0][i] / y[1][i]
            m1 += y[1][i] / y[2][i]
            m2 += y[2][i] / y[0][i]
        
        m0 /= len(x[0])
        m1 /= len(x[0])
        m2 /= len(x[0])

        print(t[0] + ' / ' + t[1] + ' = ', m0)
        print(t[1] + ' / ' + t[2] + ' = ', m1)
        print(t[2] + ' / ' + t[0] + ' = ', m2)