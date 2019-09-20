"""
Project Euler Problem 44

Problem:

Pentagonal numbers are generated by the formula, Pn=n(3n−1)/2. The first ten pentagonal numbers are:

1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference, 70 − 22 = 48, is not pentagonal.

Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference are pentagonal and D = |Pk − Pj| is
minimised; what is the value of D?
"""
from itertools import islice
from math import sqrt


def pentagonal(n: int) -> int:
    return n * (3 * n - 1) // 2


def is_pentagonal(x: int) -> int:
    root = sqrt(24 * x + 1)
    if not root.is_integer():
        return False
    iroot = int(root)
    if (1 + iroot) % 6:
        return False
    return (1 + iroot) // 6


def main() -> int:
    D = 1_000_000_000_000
    pentagonals = [pentagonal(x) for x in range(1, 2_500)]
    for idx, k in enumerate(pentagonals):
        for j in islice(pentagonals, idx):
            if is_pentagonal(j + k) and is_pentagonal(k - j):
                D = min((D, abs(k - j)))
    return D


if __name__ == '__main__':
    print(main())
