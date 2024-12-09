sample = "2333133121414131402"
sample = open("input").read()

def parse_sample(sample):
    res = []
    current_id = 0
    for i in range(len(sample)):
        if i % 2 == 0:
            res.append((current_id, int(sample[i])))
            current_id += 1
        else:
            res.append((".", int(sample[i])))
    return res

def relocate_file(parsed, r):
    l = 0
    if parsed[r][0] == ".": return parsed

    while l < r:
        if parsed[l][0] != ".":
            l += 1
            continue
        
        if parsed[l][1] == parsed[r][1]:
            parsed[l], parsed[r] = parsed[r], parsed[l]
            break
        elif parsed[l][1] > parsed[r][1]:
            r_backup = (parsed[r][0], parsed[r][1])
            parsed[l] = (parsed[l][0], parsed[l][1] - parsed[r][1])
            parsed.insert(l, parsed[r])
            parsed[r+1] = (".", r_backup[1])
            break
        else:
            l += 1
    return parsed

def relocate(parsed):
    for r in range(len(parsed)-1, -1, -1):
        relocate_file(parsed, r)
        # print("".join([str(x) for x in present(parsed)]))
    return parsed

def present(parsed):
    res = []
    for i in range(len(parsed)):
        res.extend([parsed[i][0]] * parsed[i][1])
    return res

def checksum(relocated):
    res = 0
    for i in range(len(relocated)):
        if relocated[i] == ".": continue
        res += relocated[i] * i
    return res

parsed = parse_sample(sample)
# print(parsed)
# print("".join([str(x) for x in present(parsed)]))

relocated = relocate(parsed)
presentable_relocated = present(relocated)

cs = checksum(presentable_relocated)
print(cs)

# ans: 6321896265143