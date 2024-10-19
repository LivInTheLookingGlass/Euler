from fractions import Fraction
from functools import reduce
from itertools import count, filterfalse, takewhile
from math import ceil, sqrt
from pathlib import Path
from typing import Callable, Collection, Dict, Iterable, Iterator, Optional

from sortedcontainers import SortedSet
from umsgpack import load

cache_filename = 'primes_cache.mpack'

try:
    with Path(__file__).parent.joinpath(cache_filename).open('rb') as f:
        cache = SortedSet(load(f))
except Exception:  # pragma: no cover
    cache = SortedSet([
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61
    ])
last_cached: int = cache[-1]


def primes(stop: Optional[int] = None) -> Iterator[int]:
    """Iterates over the prime numbers up to an (optional) limit, with caching.

    This iterator leverages the :py:func:`modified_eratosthenes` iterator, but adds
    additional features. The biggest is a ``stop`` argument, which will prevent it
    from yielding any numbers larger than that. The next is caching of any yielded
    prime numbers."""
    if stop is None:
        yield from cache
    else:
        yield from takewhile(stop.__gt__, cache)
    global last_cached
    if stop and last_cached > stop:
        return
    if stop is None:
        secondary = modified_eratosthenes()
    else:
        secondary = takewhile(stop.__gt__, modified_eratosthenes())
    for p in filterfalse(cache.__contains__, secondary):
        cache.add(p)
        last_cached = p
        yield p


def modified_eratosthenes() -> Iterator[int]:
    """Iterates over prime numbers using the Sieve of Eratosthenes.

    This function implements the `Sieve of Eratosthenes <https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes>`_. In
    general, it will iterate over all of the prime numbers. Below is a gif (courtesy of Wikipedia) that demonstrates
    the principle of the sieve.

    .. image:: https://upload.wikimedia.org/wikipedia/commons/9/94/Animation_Sieve_of_Eratosth.gif
        :alt: Any animated example of the Sieve of Eratosthenes"""
    # modified_eratosthenes taken, refactored from https://stackoverflow.com/a/19391111
    yield from (2, 3, 5, 7)
    sieve: Dict[int, int] = {}
    recurse = primes()
    next(recurse)
    prime = next(recurse)
    if prime != 3:
        raise ValueError()  # pragma: no cover
    prime_squared = prime * prime
    for candidate in count(9, 2):
        if candidate in sieve:  # if c is a multiple of some base prime, or
            step = sieve.pop(candidate)
        elif candidate < prime_squared:  # prime, or
            yield candidate
            continue
        else:  # the next base prime's square
            # if candidate != prime_squared:
            #     raise ValueError()
            step = prime * 2
            prime = next(recurse)
            prime_squared = prime * prime
        candidate += step  # the next multiple
        while candidate in sieve:  # make sure to not overwrite another sieve entry
            candidate += step
        sieve[candidate] = step


def prime_factors(num: int) -> Iterator[int]:
    """Iterates over the prime factors of a number."""
    if num < 0:
        yield -1
        num = -num
    if num == 0:
        yield 0
    else:
        root = ceil(sqrt(num))
        for factor in primes():
            modulo = num % factor
            if modulo == 0:
                while modulo == 0:  # double-check to call sqrt once
                    yield factor
                    num //= factor
                    modulo = num % factor
                root = ceil(sqrt(num))
            if num <= 1:
                break
            if factor > root:
                yield num
                break


def is_prime(
    num: int,
    count: int = 1,
    distinct: bool = False
) -> bool:
    """Detects if a number is prime or not.

    If a count other than 1 is given, it returns True only if the number has
    exactly count prime factors."""
    if num in (0, 1):
        return False
    factors = iter(prime_factors(num))
    if count == 1:
        if num in cache:  # always has 2
            return True
        if num % 2 == 0:
            return False
        return next(factors) == num
    seen: Collection[Optional[int]]
    seen_add: Callable[[Optional[int]], None]
    if distinct:
        seen = set()
        seen_add = seen.add
    else:
        seen = []
        seen_add = seen.append
    while None not in seen and count != len(seen):
        seen_add(next(factors, None))
    return None not in seen and next(factors, None) is None


def primes_and_negatives(*args: int) -> Iterator[int]:
    """Iterate over the primes and their negatives using :py:func:`primes`."""
    for p in primes(*args):
        yield p
        yield -p


def fast_totient(n: int, factors: Optional[Iterable[int]] = None) -> int:
    """A shortcut method to calculate Euler's totient function which assumes n has *distinct* prime factors."""
    return reduce(lambda x, y: x * (y - 1), factors or prime_factors(n), 1)


def _reduce_factors(x: Fraction, y: int) -> Fraction:
    return x * Fraction(y - 1, y)


def totient(n: int) -> int:
    """Calculates Euler's totient function in the general case."""
    total_factors = tuple(prime_factors(n))
    unique_factors = set(total_factors)
    if len(total_factors) == len(unique_factors):
        return fast_totient(n, unique_factors)

    fractional = reduce(_reduce_factors, unique_factors, Fraction(1, 1))
    return int(n * fractional)
