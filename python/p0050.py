"""
Project Euler Problem 50

Again, surprised how effective the brute force solution was

Revision 1:

Old solution stopped working for some reason. Re-did it starting from the biggest possible space this time

Problem:

The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?
"""
from typing import List

from lib.primes import is_prime, primes
from lib.iters import groupwise


def main() -> int:
    iter_primes = iter(primes())
    cached_primes: List[int] = []
    while sum(cached_primes) < 1_000_000:
        cached_primes.append(next(iter_primes))
    cached_primes.pop()
    for number in range(len(cached_primes), 21, -1):
        for group in groupwise(cached_primes, number):
            total = sum(group)
            if is_prime(total):
                return total
    return -1  # pragma: no cover


if __name__ == '__main__':
    print(main())  # pragma: no cover
