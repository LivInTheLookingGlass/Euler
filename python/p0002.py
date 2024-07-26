"""
Project Euler Problem 2

I also decided that I like lazy functions on this one. Also seen: generator
comprehensions

Revision 1:

I split fib() up so that there is one version which limits and another which
does not.

Revision 2:

Utilize the underlying pattern of the sequence to avoid needing modulo divison,
speeding up by ~2x.

Problem:

Each new term in the Fibonacci sequence is generated by adding the previous two
terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

By considering the terms in the Fibonacci sequence whose values do not exceed
four million, find the sum of the even-valued terms.

"""
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


def main() -> int:
    f = fib_by_3()  # this works because every third value is even
    answer = val = 0
    while val < 4_000_000:
        answer += val
        val = next(f)
    return answer


if __name__ == '__main__':
    print(main())  # pragma: no cover
