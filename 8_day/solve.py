import string
import numpy as np
from sympy import symbols, Eq, solve, sqrt
x, y = symbols('x y')

f = open("trial", "r")
lines = [line.strip() for line in f.readlines()]
f.close()

antennas = [char for char in string.ascii_lowercase + string.ascii_uppercase + string.digits]

m: int = len(lines)
n: int = len(lines[0])
part1: int = 0

for antenna in antennas:
    points = []
    for i in range(0, m):
        for j in range(0, n):
            if lines[i][j] == antenna:
                points.append([i,j])
    if len(points) == 0: continue
    print(antenna, ": ", points)
    for i in range(0, len(points)):
        for j in range(i+1, len(points)):
            print('[', points[i], ',', points[j], ']: ', end="")
            x1,y1 = points[i]
            x2,y2 = points[j]
            for r in range(1, int(m/2)+1):
                d = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
                if r > d or d > 3*r:
                    continue
                circle1 = Eq((x - x1)**2 + (y - y1)**2, r**2)
                circle2 = Eq((x - x2)**2 + (y - y2)**2, (2*r)**2)
                linear_eq = Eq((x - x1)**2 + (y - y1)**2 - (x - x2)**2 - (y - y2)**2, r**2 - (2*r)**2)
                linear_eq = linear_eq.simplify()
                intersection_points = solve([circle1, linear_eq], (x, y))
                print('[', end="")
                for inter_point in intersection_points:
                    x_num, y_num = map(lambda p: float(p.evalf()), inter_point)
                    print('[', x_num, y_num, ']', end="")
                    if 0 <= x_num < m and 0 <= y_num < n:
                        part1 += 1
                print(']', end = " | ")
                print(part1)

print("Part1: ", part1)