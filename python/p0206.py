"""
Project Euler Problem 206

I had to approach this by modifying the factors function from p0003, but it
seemed to work fairly well.

Problem:

Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
where each “_” is a single digit.
"""
from re import compile


def main() -> int:
    pattern = compile("1.2.3.4.5.6.7.8.9.0")
    minimum = 1010101010  # sqrt of minimum number matching pattern
    maximum = 1389026624
    step = 10  # the square is a multiple of 10, which means it's a multiple of
    # 100, since 2 and 5 are both prime. Therefore we can step by at least 10
    for x in range(minimum, maximum, step):
        if pattern.match(repr(x**2)):
            return x
    return -1


if __name__ == '__main__':
    print(main())
