"""
Project Euler Problem 50

Again, surprised how effective the brute force solution was

Problem:

The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds to a prime below
one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime,
contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most
consecutive primes?
"""
from itertools import count

from p0007 import primes, is_prime
from p0008 import groupwise


def main() -> int:
    used, highest = 21, 953
    for number in count(22):
        for idx, group in enumerate(groupwise(primes(), number)):
            total = sum(group)
            if total > 999999:
                if idx:
                    break
                else:
                    return highest
            elif is_prime(total):
                used, highest = number, total
                print(used, highest)


if __name__ == '__main__':
    print(main())
