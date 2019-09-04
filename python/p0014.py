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
from typing import Tuple


@lru_cache(maxsize=1 << 18)
def collatz_seq(n: int) -> Tuple[int, ...]:
    if n == 1:
        return ()
    elif n & 1 == 0:
        n = n // 2
    else:
        n = (3 * n + 1) // 2
    return (n, *collatz_seq(n))


def main() -> int:
    return max(
        (len(collatz_seq(x)), x) for x in range(1, 1000000)
    )[1]


if __name__ == '__main__':
    print(main())
