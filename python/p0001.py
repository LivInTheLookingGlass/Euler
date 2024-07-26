"""
Project Euler Question 1

I decided I wanted to take a funcitonal approach on this one. It also uses only
lazy functions, so it should take minimal memory usage.

Revision 1:

I found a closed form solution that works in the general case, so it's about an
order of magnitude faster now.

Problem:

If we list all the natural numbers below 10 that are multiples of 3 or 5, we
get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
"""


def summation(up_to: int, factor: int) -> int:
    n = up_to // factor
    return (n + 1) * factor * n // 2


def main() -> int:
    return summation(999, 3) + summation(999, 5) - summation(999, 15)


if __name__ == '__main__':
    print(main())  # pragma: no cover
