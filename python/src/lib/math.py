from math import factorial
from typing import Iterable


def from_digits(digs: Iterable[int], base: int = 10) -> int:
    """Reconstruct a number from a series of digits."""
    ret: int = 0
    for dig in digs:
        ret = ret * base + dig
    return ret


def lattice_paths(height: int, width: int) -> int:
    """Enumerate the paths from one corner of a Manhattan grid to its opposite."""
    return n_choose_r(height + width, height)


def n_choose_r(n: int, r: int) -> int:
    """Enumerate the number of ways to pick r elements from a collection of size n."""
    return factorial(n) // factorial(r) // factorial(n - r)


def triangle(n: int) -> int:
    """Generates the sum of 1 thru n in O(1)."""
    return n * (n + 1) // 2


def quadratic(n: int, a: int, b: int) -> int:
    return (n + a) * n + b
