"""
Project Euler Problem 32

This one was tricky because the last number was significantly higher than I
thought it would be.

Problem:

We shall say that an n-digit number is pandigital if it makes use of all the
digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1
through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing
multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity
can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only
include it once in your sum.
"""
from p0021 import proper_divisors


def main() -> int:
    answer = 0
    for product in range(10**7):
        print(product)
        for factor in proper_divisors(product):
            multiplicand = product // factor
            total = "{}{}{}".format(multiplicand, product, factor)
            if sorted(total) == ['1', '2', '3', '4', '5', '6', '7', '8', '9']:
                answer += product
                break
    return answer


if __name__ == '__main__':
    print(main())
