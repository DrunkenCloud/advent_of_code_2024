with open("input", "r") as f:
    line = f.read().strip()

temp = []
id, size = 0, 0
spaces, nums = [], []

for i in range(len(line)):
    if i % 2 == 0:
        temp.extend([id] * int(line[i]))
        nums.append([size, int(line[i]), id])
        size += int(line[i])
        id += 1
    else:
        temp.extend(["."] * int(line[i]))
        spaces.append([size, int(line[i])])
        size += int(line[i])

end = len(temp) - 1
ans = []
start = 0
while start <= end:
    if temp[start] == '.':
        while end >= start and temp[end] == '.':
            end -= 1
        if end >= start:
            ans.append(temp[end])
            end -= 1
    else:
        ans.append(temp[start])
    start += 1

part1 = sum(i * ans[i] for i in range(len(ans)))
print("Part1:", part1)

for i in range(len(nums) - 1, -1, -1):
    file_start, file_size, file_id = nums[i]
    for j, (space_start, space_size) in enumerate(spaces):
        if space_size == 0:
            continue
        if space_start < file_start and space_size >= file_size:
            nums[i][0] = space_start
            spaces[j][1] -= file_size
            spaces[j][0] += file_size
            break

part2 = sum(i * value for start, size, value in nums for i in range(start, start + size))

print("Part2:", part2)
