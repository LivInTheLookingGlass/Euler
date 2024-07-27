from math import factorial
from typing import Iterable


def n_choose_r(n: int, r: int) -> int:
    return factorial(n) // factorial(r) // factorial(n - r)


def lattice_paths(height: int, width: int) -> int:
    return n_choose_r(height + width, height)


def from_digits(digs: Iterable[int]) -> int:
    ret: int = 0
    for dig in digs:
        ret = ret * 10 + dig
    return ret


def quadratic(n: int, a: int, b: int) -> int:
    return (n + a) * n + b