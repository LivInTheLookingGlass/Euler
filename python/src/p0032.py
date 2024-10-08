"""
Project Euler Problem 32

Once I found out where the end was, it seemed to be relatively easy

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
from itertools import chain

from .lib.factors import proper_divisors
from .lib.iters import digits


def main() -> int:
    answer = 0
    list_of_digits = list(range(1, 10))
    for product in range(1000, 10**4):
        for factor in proper_divisors(product):
            multiplicand = product // factor
            covered_digits = tuple(
                chain(digits(factor), digits(multiplicand), digits(product))
            )
            if len(covered_digits) != 9:
                continue
            elif sorted(covered_digits) == list_of_digits:
                answer += product
                break
    return answer
