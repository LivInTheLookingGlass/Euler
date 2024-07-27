from math import factorial
from typing import Iterable


def from_digits(digs: Iterable[int]) -> int:
    ret: int = 0
    for dig in digs:
        ret = ret * 10 + dig
    return ret


def lattice_paths(height: int, width: int) -> int:
    return n_choose_r(height + width, height)


def n_choose_r(n: int, r: int) -> int:
    return factorial(n) // factorial(r) // factorial(n - r)


def triangle(n: int) -> int:
    return n * (n + 1) // 2


def quadratic(n: int, a: int, b: int) -> int:
    return (n + a) * n + b
