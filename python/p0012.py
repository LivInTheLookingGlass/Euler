"""
Project Euler Problem 12

Still having trouble with prime_factors, but I don't know how to make it faster
yet

Problem:

The sequence of triangle numbers is generated by adding the natural numbers. So
the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten
terms would be:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

Let us list the factors of the first seven triangle numbers:

.. code-block::

     1: 1
     3: 1,3
     6: 1,2,3,6
    10: 1,2,5,10
    15: 1,3,5,15
    21: 1,3,7,21
    28: 1,2,4,7,14,28

We can see that 28 is the first triangle number to have over five divisors.

What is the value of the first triangle number to have over five hundred
divisors?
"""
from itertools import count

from p0021 import proper_divisors


def main() -> int:
    num = 0
    for x in count(1):
        num += x
        if sum(1 for _ in proper_divisors(num)) > 500:
            return num
    return -1


if __name__ == '__main__':
    print(main())  # pragma: no cover
