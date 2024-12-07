f = open("input", "r")
lines = f.readlines()
f.close()

right_list = []
left_list = []

for line in lines:
    left, right = line.split(":")
    left_list.append(int(left.strip()))
    right_list.append(list(map(int, right.strip().split())))

def recur1(i, j, curr):
    return curr == left_list[j] if i == len(right_list[j]) else recur1(i + 1, j, curr + right_list[j][i]) or recur1(i + 1, j, curr * right_list[j][i])

def recur2(i, j, curr):
    return curr == left_list[j] if i == len(right_list[j]) else recur2(i + 1, j, curr + right_list[j][i]) or recur2(i + 1, j, curr * right_list[j][i]) or recur2(i + 1, j, int(str(curr) + str(right_list[j][i])))

part1, part2 = 0,0
for j in range(len(left_list)):
    if recur1(1, j, right_list[j][0]):
        part1 += left_list[j]

part2 = 0
for j in range(len(left_list)):
    if recur2(1, j, right_list[j][0]):
        part2 += left_list[j]
    
print("Part1:", part1)
print("Part2:", part2)