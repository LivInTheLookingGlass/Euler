"""
Project Euler Problem 58

Problem:

Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.

37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is
that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.

If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If
this process is continued, what is the side length of the square spiral for which the ratio of primes along both
diagonals first falls below 10%?
"""
from itertools import count

from .lib.iters import spiral_corners
from .lib.primes import is_prime


def main() -> int:
    total = 1
    primes = 0
    for x in count(1):
        for p in spiral_corners(x)[:3]:  # last one is a square always
            if is_prime(p):
                primes += 1
        total += 4
        if primes < total / 10:
            return 2 * x + 1
    return -1  # pragma: no cover
