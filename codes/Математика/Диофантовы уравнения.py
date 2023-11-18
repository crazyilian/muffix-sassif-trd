def bezout(a, b):
    x, xx, y, yy = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx*q
        y, yy = yy, y - yy*q
    return (a, x, y)

a, b, c = map(int, input().split())
d, k, l = bezout(a, b)
q = c // d
x, y = q*k, q*l
if c % d == 0:
    x -= x // (b//d) * (b//d)
    y = (c-a*x) // b

