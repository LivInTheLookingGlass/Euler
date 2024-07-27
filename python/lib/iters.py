from __future__ import generator_stop

from itertools import tee
from typing import Iterable, Iterator, Tuple, TypeVar

from .factors import proper_divisors

T = TypeVar("T")


def groupwise(iterable: Iterable[T], size: int) -> Iterator[Tuple[T, ...]]:
    iters = tee(iterable, size)
    for idx, x in enumerate(iters):
        for _ in range(idx):
            next(x, None)
    try:
        while True:
            yield tuple(next(x) for x in iters)
    except RuntimeError:
        pass


def abundants() -> Iterator[int]:
    for x in range(12, 28112):
        if sum(proper_divisors(x)) > x:
            yield x