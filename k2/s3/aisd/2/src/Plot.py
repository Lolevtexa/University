import os
import matplotlib.pyplot as plt
import math

ss = [
    "Checking",
    "CheckingSorted",
    "CheckingAlmostSorted",
    "CheckingReverseSorted",
    "CheckingOnSmall"
]

for s in ss:
    path = "results/" + s

    files = os.listdir(path)

    for file in files:
        f = open(path + "/" + file, "r")

        x, y = [[float(i) for i in line.split()] for line in f.read().splitlines()]
        plt.plot(x, y, "b.")


        if s != "CheckingOnSmall":
            la = 0
            lsum = 1e9
            for x1 in x:
                for y1 in y:
                    la1 = y1 / x1
                    lsum1 = 0
                    for i in range(len(x)):
                        lsum1 += abs(y[i] - x[i] * la1)

                    if lsum1 < lsum:
                        lsum = lsum1
                        la = la1

            lna = 0
            lnsum = 1e9
            for x1 in x:
                for y1 in y:
                    lna1 = y1 / x1 / math.log(x1)
                    lnsum1 = 0
                    for i in range(len(x)):
                        lnsum1 += abs(y[i] - x[i] * lna1 * math.log(x[i]))

                    if lnsum1 < lnsum:
                        lnsum = lnsum1
                        lna = lna1

            pa = 0
            pb = 0
            psum = 1e9
            x10 = [x[t] for t in range(0, len(x), 10)]
            y10 = [y[t] for t in range(0, len(y), 10)]
            for x1 in x10:
                for x2 in x10[x10.index(x1) + 1:]:
                    for y1 in y10:
                        for y2 in y10[y10.index(y1) + 1:]:
                            pa1 = (x1 * y2 - x2 * y1) / ((x2 - x1) * x1 * x2)
                            pb1 = (y1 - y2) / (x1 - x2) - pa1 * (x1 + x2)
                            psum1 = 0
                            for i in range(len(x)):
                                psum1 += abs((y[i] - (x[i]**2 * pa1 + x[i] * pb1))**2)
                            
                            if psum1 < psum:
                                psum = psum1
                                pa = pa1
                                pb = pb1
            

            xp = x[0:100]
            yp = []
            if lnsum < lsum and lnsum < 1:
                yp = [t * lna * math.log(t) for t in xp]
                print(path + "/" + file[:-4] + " nlogn", lnsum, lsum, psum, lna)
            elif lsum < 1:
                yp = [t * la for t in xp]
                print(path + "/" + file[:-4] + " n", lnsum, lsum, psum, la)
            else:
                yp = [t**2 * pa + t * pb for t in xp]
                print(path + "/" + file[:-4] + " n^2", lnsum, lsum, psum, pa, pb)
                
            plt.plot(xp, yp, "r-")
        else:
            Y = 0
            for y1 in y:
                Y += y1
            Y /= len(y)
            print(path + "/" + file[:-4] + " mid", Y)
        plt.xlabel("array size")
        plt.ylabel("sorting time (s)")

        plt.savefig("png/" + s + "/" + file[:-4] + ".png")
        plt.clf()
    print()