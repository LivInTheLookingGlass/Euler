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
from lib.fibonacci import fib_by_3


def main() -> int:
    f = fib_by_3()  # this works because every third value is even
    answer = val = 0
    while val < 4_000_000:
        answer += val
        val = next(f)
    return answer


if __name__ == '__main__':
    print(main())  # pragma: no cover
