"""
Project Euler Problem 118

This one doesn't look pretty, but it was much faster to roll out my own loop than try to make combinations() work here.
It's also more efficient because it recycles some of the number generation.

Problem:

Using all of the digits 1 through 9 and concatenating them freely to form decimal integers, different sets can be
formed. Interestingly with the set {2,5,47,89,631}, all of the elements belonging to it are prime.

How many distinct sets containing each of the digits one through nine exactly once contain only prime elements?
"""
from itertools import takewhile
from math import ceil, log10
from typing import Tuple

from .lib.primes import primes

all_digits = set("123456789")

max_digits = {
    2: 8,
    3: 7,
    4: 6,
    5: 5,
    6: 3,
}


def is_not_pandigital(*numbers: int) -> int:
    """If it's pandigital, returns 0. If not, returns the number of total digits"""
    string = "".join(str(n) for n in numbers)
    length = len(string)
    if length == 9 and set(string) == all_digits:
        return 0
    return length


def check(*numbers: int) -> Tuple[bool, bool]:
    """Returns two bools, indicating first whether to continue and second whether to increment answer."""
    if numbers[-2] >= numbers[-1]:
        return (True, False)  # otherwise we can't guarantee uniqueness
    length = is_not_pandigital(*numbers)
    if length == 9:
        return (True, False)  # this means any nested loops can't be pandigital
    if not length:
        return (True, True)  # if this set is pandigital, skip nested loops
    return (False, False)


def nest(cached_primes: Tuple[int, ...], numbers: Tuple[int, ...], digits: int) -> int:
    answer = 0
    for x in takewhile((10**(9 - digits)).__gt__, cached_primes):
        cont, inc = check(*numbers, x)
        answer += inc
        x_digits = digits + int(ceil(log10(x)))
        if not cont and len(numbers) < 6:
            answer += nest(cached_primes, (*numbers, x), x_digits)
    return answer


def main() -> int:
    answer = 0
    cached_primes = tuple(primes(98765432))  # should be largest eligible number
    for a in takewhile((10**5).__gt__, cached_primes):
        a_digits = int(ceil(log10(a)))
        answer += nest(cached_primes, (a, ), a_digits)
    return answer


if __name__ == '__main__':
    print(main())  # pragma: no cover
