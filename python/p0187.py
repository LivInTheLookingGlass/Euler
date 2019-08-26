"""
Project Euler Problem 187

I was able to chain this with a previous problem. Probably a suboptimal
solution because of it, but it felt prettier this way.

I was able to add a short-circuited fail case to the is_prime() method, though

Problem:

A composite is a number containing at least two prime factors. For example,
15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3.

There are ten composites below thirty containing precisely two, not necessarily
distinct, prime factors: 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.

How many composite integers, n < 10**8, have precisely two, not necessarily
distinct, prime factors?
"""
from itertools import combinations, takewhile
import cython

from p0007 import primes

print("Initializing primes")
_cached_primes = tuple(primes(10**8 // 2))
print("Initialized")


@cython.ccall
def cached_primes(stop):
    return takewhile(stop.__lt__, _cached_primes)


@cython.ccall
@cython.returns(cython.ulonglong)
def main() -> int:
    ten_8: cython.ulongong = 10**8
    return sum(
        1
        for y in cached_primes(ten_8 // 2)
        for x in cached_primes(y + 1)
    )


if __name__ == '__main__':
    print(main())
