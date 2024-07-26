"""
Project Euler Problem 16

Another good one for code golf

Problem:

2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
"""


def main() -> int:
    return sum(int(x) for x in repr(2**1000))


if __name__ == '__main__':
    print(main())  # pragma: no cover
