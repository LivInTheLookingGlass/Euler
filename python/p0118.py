"""
Project Euler Problem 118

This one doesn't look pretty, but it was much faster to roll out my own loop than try to make combinations() work here.
It's also more efficient because it recycles some of the number generation.

Problem:

Using all of the digits 1 through 9 and concatenating them freely to form decimal integers, different sets can be
formed. Interestingly with the set {2,5,47,89,631}, all of the elements belonging to it are prime.

How many distinct sets containing each of the digits one through nine exactly once contain only prime elements?
"""
from math import ceil, log10
import time

from p0003 import primes

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


def main() -> int:
    start = time.perf_counter()
    answer = 0

    def check(*numbers: int) -> bool:
        """Modifies answer if necessary, then returns True if you need to continue"""
        length = is_not_pandigital(*numbers)
        if length == 9 or numbers[-2] >= numbers[-1]:
            return True
        if not length:
            nonlocal answer
            answer += 1
            return True
        return False

    try:
        for a in primes(10**5):
            a_digits = ceil(log10(a))
            for b in primes(10**(9 - a_digits)):
                if check(a, b):
                    continue
                b_digits = ceil(log10(b))
                for c in primes(10**(9 - a_digits - b_digits)):
                    if check(a, b, c):
                        continue
                    c_digits = ceil(log10(c))
                    for d in primes(10**(9 - a_digits - b_digits - c_digits)):
                        if check(a, b, c, d):
                            continue
                        d_digits = ceil(log10(d))
                        for e in primes(10**(9 - a_digits - b_digits - c_digits - d_digits)):
                            if check(a, b, c, d, e):
                                continue
                            e_digits = ceil(log10(e))
                            for f in primes(10**(9 - a_digits - b_digits - c_digits - d_digits - e_digits)):
                                if check(a, b, c, d, e, f):
                                    continue
    finally:
        print(time.perf_counter() - start)
    return answer


if __name__ == '__main__':
    print(main())
