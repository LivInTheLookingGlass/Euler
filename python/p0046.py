"""
Project Euler Problem 46

Didn't even need to rearrange the formula to solve it trivially

Revision 1:

It turns out that rearranging the formula let me cut the time by ~50x

Problem:

It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a
square.

9 = 7 + 2×1^2
15 = 7 + 2×2^2
21 = 3 + 2×3^2
25 = 7 + 2×3^2
27 = 19 + 2×2^2
33 = 31 + 2×1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
"""
from itertools import count, takewhile
from math import ceil, sqrt

from p0003 import primes
from p0007 import is_prime


def main() -> int:
    cached_primes = tuple(primes(6000))
    for goal in count(35, 2):
        if is_prime(goal):
            continue
        for p in takewhile(goal.__gt__, cached_primes):
            done = False
            for x in range(1, ceil(sqrt((goal - p) / 2)) + 1):
                if p + 2 * x * x == goal:
                    done = True
                    break
            if done:
                break
        else:
            return goal
    return -1


if __name__ == '__main__':
    print(main())  # pragma: no cover
