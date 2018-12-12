"""
Project Euler Problem 134

Officially I have this solved, but it took 76 core-minutes, which is just not a
reasonable runtime. I have made some minor optimizations in the hopes that it
will be reduced further, but it only went down to 37 core-minutes. Not good
enough.

Problem:

Consider the consecutive primes p1 = 19 and p2 = 23. It can be verified that
1219 is the smallest number such that the last digits are formed by p1 whilst
also being divisible by p2.

In fact, with the exception of p1 = 3 and p2 = 5, for every pair of consecutive
primes, p2 > p1, there exist values of n for which the last digits are formed
by p1 and n is divisible by p2. Let S be the smallest of these values of n.

Find ∑ S for every pair of consecutive primes with 5 ≤ p1 ≤ 1000000.
"""
from itertools import count

import cython

from p0007 import primes


@cython.ccall
@cython.locals(p2=cython.ulonglong, n=cython.ulonglong)
@cython.returns(cython.ulonglong)
def main() -> int:
    answer: cython.ulonglong = 0
    pow_10: cython.ulong = 10
    iterator = primes(1000000)  # iterate over primes <1000000
    next(iterator)  # skip 2
    next(iterator)  # skip 3
    p1: cython.ulonglong = next(iterator)  # p1 = 5
    for p2 in iterator:  # 7, 11, 13, 17, ...
        while pow_10 < p1:
            pow_10 *= 10
        for n in count(p2 * 3, p2 * 2):  # 3p2, 5p2, 7p2, ...
            if n % pow_10 == p1:
                answer += n
                p1 = p2
                break
    return answer


if __name__ == '__main__':
    print(main())
