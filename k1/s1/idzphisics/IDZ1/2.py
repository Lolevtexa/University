from math import *

A = 1
w = 1
fi1 = 3
fi2 = 1
n = 1
m = 2
alf = 0.2
bet = 0.1

x2 = lambda t: A * sin(n * w * t      ) * exp(-alf * t)
y2 = lambda t: A * sin(m * w * t + fi2) * exp(-bet * t)
ax = lambda t: A * exp(-alf * t) * ((alf**2 - n**2 * w**2) * sin(n * w * t      ) - 2 * alf * n * w * cos(n * w * t      ))
ay = lambda t: A * exp(-bet * t) * ((bet**2 - m**2 * w**2) * sin(m * w * t + fi2) - 2 * bet * m * w * cos(m * w * t + fi2))

a = lambda t: ax(t)**2 + ay(t)**2

k = 1e-4

amax = a(0)
tres = 0
for i in range(int(0 / k), int(10 / k + 1)):
    t = i * k
    tmp = a(t)
    if amax < tmp:
        amax = tmp
        tres = t

print(sqrt(amax), x2(tres), y2(tres))