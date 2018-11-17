"""
Project Euler Problem 3

More lazy functions this time. Took a little while to figure out how to
eliminate the special case for 2.

Revision 1:

I changed the implementation of prime_factors() to stop checking if factors
exceed the square root of the number. This eliminates a lot of checking for
numbers which could not possibly be the factor.

Revision 2:

Changed prime_factors to catch accidental 0s and -1s, further optimize sqrt
checks, and added a persistant cache of primes to reduce the space that needs
checking

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
"""
from atexit import register
from itertools import chain, count
from umsgpack import load, dump
from math import sqrt
from typing import Iterator

from ordered_set import OrderedSet

cache_filename = 'p0003_cache.mpack'


class prime_factors(object):
    __slots__ = ('num', )
    try:
        with open(cache_filename, 'rb+') as f:
            cache = OrderedSet(load(f))
            last_cached = cache[-1]
    except (ImportError, IOError, FileNotFoundError):
        cache = OrderedSet([
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61
        ])
        last_cached = 67

    def __init__(self, num: int) -> None:
        """
        Iterates over the prime factors of a number (and also 0, -1)

        Since it starts at small numbers, it never needs to check if a factor
        is indeed prime, since all smaller factors have been tried beforehand.
        """
        self.num = num

    def __iter__(self) -> Iterator[int]:
        num = self.num
        if num < 0:
            yield -1
            num = -num
        if num == 0:
            yield 0
        else:
            root = int(sqrt(num)) + 1
            candidates = chain(
                prime_factors.cache, count(prime_factors.last_cached, 2)
            )
            for factor in candidates:  # cache, then odd numbers afterwards
                if num % factor == 0:
                    while num % factor == 0:  # double-check to call sqrt once
                        yield factor
                        num //= factor
                    root = int(sqrt(num)) + 1
                    prime_factors.cache.add(factor)
                    if prime_factors.last_cached <= factor:
                        prime_factors.last_cached = factor + 2
                if num <= 1:
                    break
                if factor > root:
                    yield num
                    break

    @staticmethod
    @register
    def cleanup():
        with open(cache_filename, 'wb') as f:
            dump(tuple(prime_factors.cache), f)


def main() -> int:
    return max(prime_factors(600851475143))


if __name__ == '__main__':
    print(main())
