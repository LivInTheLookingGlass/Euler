from math import factorial, sqrt
from typing import Iterable


def from_digits(digs: Iterable[int], base: int = 10) -> int:
    """Reconstruct a number from a series of digits.

    Runs in :math:`O(n)` operations, where :math:`n` is the number of digits. This means that it will take
    :math:`O(\\log(m))` where :math:`m` is the original number."""
    ret: int = 0
    for dig in digs:
        ret = ret * base + dig
    return ret


def lattice_paths(height: int, width: int) -> int:
    """Enumerate the paths from one corner of a Manhattan grid to its opposite."""
    return n_choose_r(height + width, height)


def mul_inv(a: int, b: int) -> int:
    """Multiplicative inverse for modulo numbers

    Runs in :math:`O(\\log(\\min(a, b)))` time. Given that this is typically used in the context of modulus math, we
    can usually assume :math:`a < b`, simplifying this to :math:`O(\\log(a))` time."""
    if b == 1:
        return 1
    b0: int = b
    x0: int = 0
    x1: int = 1
    while a > 1:
        q: int = a // b
        a, b = b, a % b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0:
        return x1 + b0
    return x1


def n_choose_r(n: int, r: int) -> int:
    """Enumerate the number of ways to pick r elements from a collection of size n.

    Runs in :math:`O(n)` multiplications. Because of how Python works, numbers less than :math:`2^{64}` will multiply
    in constant time. Larger numbers, however, will multiply in :math:`O(n^{1.585})`, giving an overall time complexity
    of :math:`O(n^{2.585})`."""
    return factorial(n) // factorial(r) // factorial(n - r)


def triangle(n: int) -> int:
    """Generates the sum of 1 thru n in O(1)."""
    return n * (n + 1) // 2


def quadratic(n: int, a: int, b: int) -> int:
    return (n + a) * n + b


def pentagonal(n: int) -> int:
    return n * (3 * n - 1) // 2


def is_pentagonal(x: int) -> int:
    root = sqrt(24 * x + 1)
    if not root.is_integer():
        return False
    iroot = int(root)
    if (1 + iroot) % 6:
        return False
    return (1 + iroot) // 6


def hexagonal(n: int) -> int:
    return n * (2 * n - 1)
