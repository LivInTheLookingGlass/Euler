from __future__ import generator_stop

from itertools import count, tee
from typing import Iterable, Iterator, Optional, Tuple, TypeVar

from .factors import proper_divisors

T = TypeVar("T")


def groupwise(iterable: Iterable[T], size: int) -> Iterator[Tuple[T, ...]]:
    """Iterate over something in buckets of a given size."""
    iters = tee(iterable, size)
    for idx, x in enumerate(iters):
        for _ in range(idx):
            next(x, None)
    try:
        while True:
            yield tuple(next(x) for x in iters)
    except RuntimeError:
        pass


def abundants(stop: Optional[int] = None) -> Iterator[int]:
    """Iterate over the abundant numbers."""
    if stop is None:
        iterator: Iterable[int] = count(12)
    else:
        iterator = range(12, stop)
    for x in iterator:
        if sum(proper_divisors(x)) > x:
            yield x


def digits(x: int, base: int = 10) -> Iterator[int]:
    """Iterate over the digits of a number in a given base."""
    while x:
        x, y = divmod(x, base)
        yield y
