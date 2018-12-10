"""
Project Euler Problem 41

Once I found out where the end was, it seemed to be relatively easy

Problem:

We shall say that an n-digit number is pandigital if it makes use of all the
digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
also prime.

What is the largest n-digit pandigital prime that exists?
"""

from p0007 import primes
from p0074 import digits


def main() -> int:
    answer = -1
    for p in primes():
        cur_digits = tuple(digits(p))
        num_digits = len(cur_digits)
        if num_digits > 7:
            break
        elif any(
            digit > num_digits or
            cur_digits.count(digit) != 1
            for digit in cur_digits
        ):
            continue
        elif p > answer:
            answer = p
    return answer


if __name__ == '__main__':
    print(main())
