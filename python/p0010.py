"""
Project Euler Problem 10

This one was also relatively easy, but the problem I am running into is that my
original implementation of primes() is not very fast. I did go back and
refactor that, but I think I could do better. Maybe I will pass these through
cython at some point.

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
"""
from itertools import takewhile

from p0007 import primes


def main() -> int:
    return sum(takewhile(lambda x: x < 2000000, primes()))


if __name__ == '__main__':
    print(main())
