"""
Project Euler Problem 70

My time as a TA in the Discrete Mathematics class really paid off here

Problem:

Euler's totient function, $\\phi(n)$ [sometimes called the phi function], is used to determine the number of positive
numbers less than or equal to $n$ which are relatively prime to $n$. For example, as $1, 2, 4, 5, 7$, and $8$, are all
less than nine and relatively prime to nine, $\\phi(9)=6$.<br>The number $1$ is considered to be relatively prime to
every positive number, so $\\phi(1)=1$.

Interestingly, $\\phi(87109)=79180$, and it can be seen that $87109$ is a permutation of $79180$.

Find the value of $n$, $1 \\lt n \\lt 10^7$, for which $\\phi(n)$ is a permutation of $n$ and the ratio $n/\\phi(n)$
produces a minimum.
"""
from functools import reduce
from itertools import chain

from .lib.primes import prime_factors


def totient(n: int) -> int:
    return reduce(lambda x, y: x * (y - 1), prime_factors(n), 1)


def main() -> int:
    answer = 0
    ratio = float('inf')
    stop = 10 ** 7
    # restrict to 2k + 1, as 2 is a very common factor
    # restrict to 3k ± 1, as 3 is a very common factor
    # restrict to 6k ± 1, combining the above
    for x in chain.from_iterable(zip(
      range(6 - 1, stop, 30),   # 6k - 1, x ≡ 1 (mod 5)
      range(6 + 1, stop, 30),   # 6k + 1, x ≡ 1 (mod 5)
      range(6 + 5, stop, 30),   # 6k - 1, x ≡ 2 (mod 5)
      range(6 + 7, stop, 30),   # 6k + 1, x ≡ 2 (mod 5)
      range(6 + 11, stop, 30),  # 6k - 1, x ≡ 3 (mod 5)
      range(6 + 13, stop, 30),  # 6k + 1, x ≡ 3 (mod 5)
      range(6 + 17, stop, 30),  # 6k - 1, x ≡ 4 (mod 5)
      range(6 + 19, stop, 30)   # 6k + 1, x ≡ 4 (mod 5)
    )):
        t = totient(x)
        strx = str(x)
        strt = str(t)
        if not all(strx.count(d) == strt.count(d) for d in set(strx)):
            continue
        nratio = x / t
        if nratio < ratio:
            answer = x
            ratio = nratio
    return answer
