"""
Project Euler Problem 63

Problem:

The 5-digit number, 16807 = 7**5, is also a fifth power.
Similarly, the 9-digit number, 134217728 = 8**9, is a ninth power.

How many n-digit positive integers exist which are also an nth power?
"""
from typing import Dict, Tuple


def main() -> int:
    seen: Dict[Tuple[int, int], int] = {}
    for x in range(1, 10):
        for n in range(1, 100):
            if len(str(x**n)) == n:
                seen[x, n] = x**n
    return len(seen)


if __name__ == '__main__':
    print(main())  # pragma: no cover
