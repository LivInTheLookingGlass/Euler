"""
Project Euler Problem 31

This one was tricky because the last number was significantly higher than I
thought it would be.

Problem:

In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
"""
from itertools import count

units = (200, 100, 50, 20, 10, 5, 2, 1)


def main() -> int:
    answer = 0
    spans = [range(200 // unit + 1) for unit in units]
    counts = [0 for _ in spans]
    while counts[0] in spans[0]:
        counts[-1] += 1
        for x in range(-1, -len(counts), -1):
            if counts[x] not in spans[x]:
                counts[x] = 0
                counts[x - 1] += 1
                curr_total = sum(
                    a * b for a, b in zip(counts[:x - 1], units[:x - 1])
                )
                spans[x] = range(200 - curr_total // units[x] + 1)
                spans[x - 1] = range(200 - curr_total // units[x - 1] + 1)
            else:
                break
        if sum(a * b for a, b in zip(counts, units)) == 200:
            answer += 1
            print(
                ",  ".join(
                    "{:03}p * {{:03}}".format(unit) for unit in units
                ).format(*counts)
            )
    return answer


if __name__ == '__main__':
    print(main())
