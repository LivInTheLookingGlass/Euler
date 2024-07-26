
from typing import Iterator


def fib() -> Iterator[int]:
    """This generator goes through the fibonacci sequence"""
    a, b = 0, 1
    while True:
        yield b
        a, b = b, a + b


def fib_by_3(start_index: int = 0) -> Iterator[int]:
    """This generator goes through the fibonacci sequence skipping by 3s. This works because:
    F[n] = F[n-1]          + F[n-2]
    F[n] = F[n-2] + F[n-3] + F[n-2]
    F[n] = 2 * F[n-2]            + F[n-3]
    F[n] = 2 * (F[n-3] + F[n-4]) + F[n-3]
    F[n] = 3 * F[n-3] + 2 * F[n-4]
    F[n] = 3 * F[n-3] + F[n-4] + F[n-5] + F[n-6]
    F[n] = 4 * F[n-3]                   + F[n-6]
    """
    orig = fib()
    a = 0
    if start_index:
        for _ in range(start_index - 1):
            next(orig)
        a = next(orig)
    next(orig)  # start + 1
    next(orig)  # start + 2
    b = next(orig)  # start + 3
    del orig
    yield a
    while True:
        yield b
        a, b = b, a + b * 4