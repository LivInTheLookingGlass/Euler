from typing import Iterable


def from_digits(digs: Iterable[int]) -> int:
    ret: int = 0
    for dig in digs:
        ret = ret * 10 + dig
    return ret


def quadratic(n: int, a: int, b: int) -> int:
    return (n + a) * n + b