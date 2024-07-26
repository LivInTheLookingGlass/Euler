"""
Project Euler Problem 97

This one ended up being fairly easy to run, since Python integers can be an
arbitrary size

Problem:

The first known prime found to exceed one million digits was discovered in
1999, and is a Mersenne prime of the form 26972593−1; it contains exactly
2,098,960 digits. Subsequently other Mersenne primes, of the form 2p−1, have
been found which contain more digits.

However, in 2004 there was found a massive non-Mersenne prime which contains
2,357,207 digits: 28433×27830457+1.

Find the last ten digits of this prime number.
"""


def main() -> int:
    return ((28433 << 7830457) + 1) % 10**10


if __name__ == '__main__':
    print(main())  # pragma: no cover
