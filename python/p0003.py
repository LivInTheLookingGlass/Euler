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

Revision 3:

Move primes() to p0003 in order to fix caching. Switch to a prime number sieve
for generating new primes for the cache.

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
"""
from lib.primes import prime_factors


def main() -> int:
    return max(prime_factors(600851475143))


if __name__ == '__main__':
    print(main())  # pragma: no cover
