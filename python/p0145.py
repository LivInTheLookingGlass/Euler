"""
Project Euler Problem 145

Problem:

Some positive integers n have the property that the sum [ n + reverse(n) ] consists entirely of odd (decimal) digits.
For instance, 36 + 63 = 99 and 409 + 904 = 1313. We will call such numbers reversible; so 36, 63, 409, and 904 are
reversible. Leading zeroes are not allowed in either n or reverse(n).

There are 120 reversible numbers below one-thousand.

How many reversible numbers are there below one-billion (10^9)?
"""
from itertools import chain
from typing import Iterable

from p0052 import digits


def from_digits(digs: Iterable[int]) -> int:
    ret: int = 0
    for dig in digs:
        ret = ret * 10 + dig
    return ret


def main():
    import time
    start = time.clock()
    seen = set()
    for x in range(10**9 // 2):
        if not (x % 10) or x in seen:
            continue  # divisible by 10, therefore reversed would have leading zeroes
        inverse = from_digits(reversed(digits(x)))
        if all(digit % 2 for digit in digits(x + inverse)):
            # print(x, inverse)
            seen.update((x, inverse))
    print(time.clock() - start)
    return len(seen)


if __name__ == '__main__':
    print(main())
