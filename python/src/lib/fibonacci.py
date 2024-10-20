from typing import Iterator

from .iters import consume


def fib() -> Iterator[int]:
    """This generator goes through the fibonacci sequence
    
    Generating each new element happens in constant time."""
    a, b = 0, 1
    while True:
        yield b
        a, b = b, a + b


def fib_by_3(start_index: int = 0) -> Iterator[int]:
    """This generator goes through the fibonacci sequence skipping by 3s. This works because:

    .. code-block:: python

      F[n] = F[n-1]          + F[n-2]
      F[n] = F[n-2] + F[n-3] + F[n-2]
      F[n] = 2 * F[n-2]            + F[n-3]
      F[n] = 2 * (F[n-3] + F[n-4]) + F[n-3]
      F[n] = 3 * F[n-3] + 2 * F[n-4]
      F[n] = 3 * F[n-3] + F[n-4] + F[n-5] + F[n-6]
      F[n] = 4 * F[n-3]                   + F[n-6]

    Generating each new element happens in constant time, and setup takes :math:`O(n)` where :math:`n` is the given
    start index."""
    orig = fib()
    a = 0
    consume(orig, start_index)
    next(orig)  # start + 1
    next(orig)  # start + 2
    b = next(orig)  # start + 3
    del orig
    yield a
    while True:
        yield b
        a, b = b, a + b * 4
