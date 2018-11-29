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

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
the 6th prime is 13.

What is the 10 001st prime number?
"""
from itertools import chain, count
from typing import Iterator, Optional, Set

from p0003 import prime_factors


def is_prime(num: int, count: int = 1, distinct: bool = False) -> bool:
    """Detects if a number is prime or not.

    If a count other than 1 is given, it returns True only if the number has
    exactly count prime factors. The distinct flag will have it look only for
    unique prime factors."""
    if num in (0, 1):
        return False
    factors = iter(prime_factors(num))
    if count == 1:
        if num in prime_factors.cache:
            return True
        next(factors)
        return next(factors, None) is None
    else:
        seen: Set[Optional[int]] = set()
        while None not in seen and count != len(seen):
            seen.add(next(factors, None))
        return None not in seen and next(factors, None) is None


def primes() -> Iterator[int]:
    for num in chain((2, ), count(3, 2)):  # 2, then 3, 5, 7, 9, 11, 13, ...
        if is_prime(num):
            yield num


def main() -> int:
    for idx, num in enumerate(primes(), 1):
        if idx == 10001:
            return num
    return -1


if __name__ == '__main__':
    print(main())
