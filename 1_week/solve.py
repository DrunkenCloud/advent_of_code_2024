def main():
    with open("input", "r") as f:
        data = f.readlines()

    column1 = [int(line.split()[0]) for line in data]
    column2 = [int(line.split()[-1]) for line in data]

    column1 = sorted(column1)
    column2 = sorted(column2)

    part1 = sum(abs(column1[i] - column2[i]) for i in range(len(column1)))

    from collections import Counter
    counter = Counter(column2)

    part2 = sum(n * counter.get(n, 0) for n in column1)

    print(f"Part 1: {part1}")
    print(f"Part 2: {part2}")


if __name__ == "__main__":
    main()
