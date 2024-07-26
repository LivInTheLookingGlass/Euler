"""
Project Euler Problem 31

This took a while to get in a form that I was happy with. I wanted something
more flexible than "let's take 8 for loops", so I did my best to make this as
modular as I could think to do.

Problem:

In England the currency is made up of pound, £, and pence, p, and there are
eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
"""
from typing import Iterable, MutableSequence, Sequence


def calculate(counts: Iterable[int], units: Iterable[int]) -> int:
    return sum(a * b for a, b in zip(counts, units))


def coin_combinations(amount: int, units: Sequence[int], counts: MutableSequence[int]) -> int:
    answer = total = 0
    while total <= amount:
        total = calculate(counts, units)
        if total == amount:
            # print(
            #     ",  ".join(
            #         "{:03}p * {{:03}}".format(unit) for unit in units
            #     ).format(*counts)
            # )
            answer += 1
        counts[-1] += 1
        key = len(counts)
        while total > amount:
            key -= 1
            counts[key] = 0
            counts[key - 1] += 1
            total = calculate(counts, units)
            if key == 1:
                break
    return answer


def main() -> int:
    units = (200, 100, 50, 20, 10, 5, 2, 1)
    counts = [0 for _ in units]
    return coin_combinations(200, units, counts)


if __name__ == '__main__':
    print(main())  # pragma: no cover
