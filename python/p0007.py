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

Revision 4:

Switch to takewhile, use prime cache again

Revision 5:

Move primes() to p0003 in order to fix caching

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
the 6th prime is 13.

What is the 10 001st prime number?
"""
from lib.primes import primes


def main() -> int:
    for idx, num in enumerate(primes(), 1):
        if idx == 10001:
            return num
    return -1


if __name__ == '__main__':
    print(main())  # pragma: no cover
