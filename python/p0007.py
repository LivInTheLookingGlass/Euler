"""
Project Euler Problem 7

I was able to chain this with a previous problem. Probably a suboptimal
solution because of it, but it felt prettier this way.

I was able to add a short-circuited fail case to the is_prime() method, though

Revision 1:

Add a shortcut on is_prime to check the pfs cache first, and refactored to work
with the new pfs object and name

Revision 2:

Add a count to the trigger on prime numbers

Revision 3:

Add a stop parameter to primes()

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
the 6th prime is 13.

What is the 10 001st prime number?
"""
from itertools import chain, count
from typing import Iterator, List, Optional, Set

import cython

from p0003 import prime_factors


@cython.final
@cython.ccall
def is_prime(
    num: cython.ulonglong,
    count: cython.ulonglong = 1,
    distinct: cython.bint = False
) -> cython.bint:
    """Detects if a number is prime or not.

    If a count other than 1 is given, it returns True only if the number has
    exactly count prime factors."""
    if num in (0, 1):
        return False
    factors = iter(prime_factors(num))
    if count == 1:
        if num in prime_factors.cache:  # always has 2
            return True
        elif num % 2 == 0:
            return False
        next(factors)
        return next(factors, None) is None
    else:
        if distinct:
            seen: Set[Optional[cython.ulonglong]] = set()
            seen_add = seen.add
        else:
            seen: List[Optional[cython.ulonglong]] = []
            seen_add = seen.append
        while None not in seen and count != len(seen):
            seen_add(next(factors, None))
        return None not in seen and next(factors, None) is None


@cython.final
@cython.ccall
@cython.locals(num=cython.ulonglong)
def primes(stop=None) -> Iterator[int]:
    if stop is None:
        primary = prime_factors.cache
    else:
        primary = (x for x in prime_factors.cache if x < stop)
    yield from primary
    if stop is None:
        secondary = count(prime_factors.last_cached, 2)
    else:
        secondary = range(prime_factors.last_cached, stop, 2)
    yield from filter(is_prime, secondary)


def main() -> int:
    for idx, num in enumerate(primes(), 1):
        if idx == 10001:
            return num
    return -1


if __name__ == '__main__':
    print(main())
