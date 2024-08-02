"""
Project Euler Problem 14

I did a naive approach where I just built the whole sequence.

Revision 1:

I reformulated this to build a sequence length instead of the sequence. Should
use less memory and take less time.

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
from typing import MutableMapping


def collatz_len(n: int, cache: MutableMapping[int, int]) -> int:
    if n in cache:
        return cache[n]
    if n == 1:
        result = 0
    elif n & 1 == 0:
        result = 1 + collatz_len(n // 2, cache)
    else:
        result = 2 + collatz_len((3 * n + 1) // 2, cache)
    cache[n] = result
    return result


def main() -> int:
    cache: MutableMapping[int, int] = {}
    return max(
        (collatz_len(x, cache), x) for x in range(1, 1000000)
    )[1]


if __name__ == '__main__':
    print(main())  # pragma: no cover
