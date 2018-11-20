"""
Project Euler Problem 14

I couldn't figure out how to do this as efficiently as I would have liked. I am
SURE that there is a better way to check if a number is a palindrome, but I
could not think of one.

Problem:

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains
10 terms. Although it has not been proved yet (Collatz Problem), it is thought
that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
"""
from functools import lru_cache
from typing import Iterator

import cython


@lru_cache(maxsize=10240)
@cython.cfunc
@cython.locals(n=cython.ulonglong)
@cython.returns(cython.ulonglong)
def collatz(n: cython.ulonglong) -> cython.ulonglong:
    if n % 2 == 0:
        return n // 2
    else:
        return (3 * n + 1) // 2


@cython.cfunc
@cython.locals(n=cython.ulonglong)
def collatz_seq(n: int) -> Iterator[int]:
    while n > 1:
        yield n
        n = collatz(n)


@cython.cfunc
@cython.returns(cython.ulonglong)
@cython.locals(x=cython.ulonglong, result=cython.ulonglong,
               length=cython.ulonglong, new_length=cython.ulonglong)
def main() -> int:
    result, length = 0, 0
    for x in range(1, 1000000):
        print(x)
        new_length = sum(1 for _ in collatz_seq(x))
        if new_length > length:
            result, length = x, new_length
    return result


if __name__ == '__main__':
    print(main())
