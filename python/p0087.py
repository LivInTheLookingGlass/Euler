"""
Project Euler Problem 87

I ended up having to do this with recursion, which I normally do not like to
use that much. Small changes can have large effects on later results. Still,
this seems to work for the moment.

Problem:

The smallest number expressible as the sum of a prime square, prime cube, and
prime fourth power is 28. In fact, there are exactly four numbers below fifty
that can be expressed in such a way:

28 = 2**2 + 2**3 + 2**4
33 = 3**2 + 2**3 + 2**4
49 = 5**2 + 2**3 + 2**4
47 = 2**2 + 3**3 + 2**4

How many numbers below fifty million can be expressed as the sum of a prime
square, prime cube, and prime fourth power?
"""
from p0007 import primes


def main() -> int:
    seen = set()
    for x in primes():
        x2 = x**2
        if x2 > 49999999:
            break
        for y in primes():
            y3 = y**3
            if x2 + y3 > 49999999:
                break
            for z in primes():
                z4 = z**4
                if x2 + y3 + z4 > 49999999:
                    break
                else:
                    seen.add(x2 + y3 + z4)
    return len(seen)


if __name__ == '__main__':
    print(main())
