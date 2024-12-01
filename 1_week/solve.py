from functools import reduce

def main():
    with open("input", "r") as f:
        data = f.readlines()

    column1 = sorted([int(line.split()[0]) for line in data])
    column2 = sorted([int(line.split()[-1]) for line in data])

    part1 = map(lambda x,y : abs(x - y), column1, column2)
    part1 = reduce(lambda x,y:  x+y, part1)

    from collections import Counter
    counter = Counter(column2)

    part2 = sum(n * counter.get(n, 0) for n in column1)

    print(f"Part 1: {part1}")
    print(f"Part 2: {part2}")


if __name__ == "__main__":
    main()
