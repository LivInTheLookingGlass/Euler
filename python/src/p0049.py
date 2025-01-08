"""
Project Euler Problem 49

I was surprised how fast my brute-force solution went, but it worked

Problem:

The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases
by 3330, is unusual in two ways: (i) each of the three terms are prime, and,
(ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes,
exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this
sequence?
"""
from itertools import takewhile, tee

from .lib.iters import consume, digits
from .lib.primes import primes


def main() -> int:
    primes_at_1000 = primes(10000)
    consume(takewhile((1000).__gt__, primes_at_1000))
    primes_at_1000, pgen_1 = tee(primes_at_1000)
    for p1 in pgen_1:
        if p1 == 1487:
            continue
        pgen_1, pgen_2 = tee(pgen_1)
        for p2 in pgen_2:
            if p2 > 10000 - p1 // 2:
                break
            pgen_2, pgen_3 = tee(pgen_2)
            for p3 in pgen_3:
                dp1p2 = p1 - p2
                dp2p3 = p2 - p3
                if dp1p2 < dp2p3:
                    continue
                elif dp1p2 > dp2p3:
                    break
                elif set(digits(p1)) == set(digits(p2)) == set(digits(p3)):
                    return p1 * 10**8 + p2 * 10**4 + p3
    return -1  # pragma: no cover
