from math import *

A = 1
w = 1
fi1 = 3
fi2 = 1
n = 1
m = 2
alf = 0.2
bet = 0.1

x1 = lambda t: A * sin(m * w * t      ) * exp(-alf * t)
y1 = lambda t: A * sin(n * w * t + fi1) * exp(-bet * t)
x2 = lambda t: A * sin(n * w * t      ) * exp(-alf * t)
y2 = lambda t: A * sin(m * w * t + fi2) * exp(-bet * t)

R = lambda t: (x1(t) - x2(t)) ** 2 + (y1(t) - y2(t)) ** 2

k = 1e-5

res = R(4)
for i in range(int(4 / k), int(10 / k + 1)):
    t = i * k
    res = max(res, R(t))

print(sqrt(res))