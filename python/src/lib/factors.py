from functools import reduce
from itertools import combinations
from operator import mul
from typing import Iterator, Set

from .primes import prime_factors


def proper_divisors(num: int) -> Iterator[int]:
    """Iterate over the proper divisors of a given number.
    
    Given that it will generate a max of :math:`\\log(n)` factors, the binomial theorem tells us this should take
    :math:`O(2^{\\log(n)}) = O(n)` operations."""
    factors = tuple(prime_factors(num))
    seen: Set[int] = set()
    yield 1
    for x in range(1, len(factors)):
        for combo in combinations(factors, x):
            ret = reduce(mul, combo, 1)
            if ret not in seen:
                yield ret
                seen.add(ret)
        seen.clear()
