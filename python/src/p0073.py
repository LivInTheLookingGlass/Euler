"""
Project Euler Problem 73

The biggest problem with this was remembering how to do groupwise()

Revision 1:

By making the boundary conditions better-defined, I was able to shave off a few seconds

Problem:

Consider the fraction, n/d, where n and d are positive integers. If n<d and
HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of
size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7,
3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that there are 3 fractions between 1/3 and 1/2.

How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper
fractions for d ≤ 12,000?
"""
from fractions import Fraction
from typing import Set, Tuple


def main() -> int:
    seen: Set[Tuple[int, int]] = set()
    for x in range(2, 12001):
        for y in range(x // 3 + 1, (x + 1) // 2):
            f = Fraction(y, x)
            seen.add((f.numerator, f.denominator))
    return len(seen)
