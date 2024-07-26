"""
Project Euler Problem 21

I had to approach this by modifying the factors function from p0003, but it
seemed to work fairly well.

Revision 1:

Rewrote the proper_divisors function to be significantly faster by leveraging
the prime_factors object.

Problem:

Let d(n) be defined as the sum of proper divisors of n (numbers less than n
which divide evenly into n). If d(a) = b and d(b) = a, where a ≠ b, then a and
b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55
and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and
142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
"""
from functools import reduce
from itertools import combinations, filterfalse
from operator import mul
from typing import Iterator, Set

from lib.primes import prime_factors


def proper_divisors(num: int) -> Iterator[int]:
    factors = tuple(prime_factors(num))
    seen: Set[int] = set()
    yield 1
    for x in range(1, len(factors)):
        for combo in combinations(factors, x):
            ret = reduce(mul, combo, 1)
            if ret not in seen:
                yield ret
                seen.add(ret)
        seen.clear()


def d(n: int) -> int:
    return sum(proper_divisors(n))


def main() -> int:
    ret = 0
    skip: Set[int] = set()
    for a in filterfalse(skip.__contains__, range(10000)):
        b = d(a)
        if a != b and d(b) == a:
            ret += a + b
            skip.add(b)
    return ret


if __name__ == '__main__':
    print(main())  # pragma: no cover
