"""
Project Euler Problem 52

Problem:

It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different
order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
"""
from itertools import count
from typing import Set


def digits(n: int) -> Set[int]:
    ret = set()
    while n:
        n, digit = divmod(n, 10)
        ret.add(digit)
    return ret


def main():
    for x in count(1):
        orig = digits(x)
        if all(digits(x * y) == orig for y in range(2, 7)):
            return x


if __name__ == '__main__':
    print(main())
