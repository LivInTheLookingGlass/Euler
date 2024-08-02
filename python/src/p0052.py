"""
Project Euler Problem 52

Problem:

It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different
order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.

Revision 1:

Changed to return a list instead of a set so it can be used in other problems
"""
from itertools import count

from .lib.iters import digits


def main() -> int:
    for x in count(1):
        orig = {*digits(x)}
        if all({*digits(x * y)} == orig for y in range(2, 7)):
            return x
    return -1  # pragma: no cover


if __name__ == '__main__':
    print(main())  # pragma: no cover
