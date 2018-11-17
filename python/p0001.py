"""
Project Euler Question 1

I decided I wanted to take a funcitonal approach on this one. It also uses only
lazy functions, so it should take minimal memory usage.

Problem:

If we list all the natural numbers below 10 that are multiples of 3 or 5, we
get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.

"""


def main():
    total = sum(range(0, 1000, 3)) + sum(range(0, 1000, 5))
    return total - sum(range(0, 1000, 15))


if __name__ == '__main__':
    print(main())
