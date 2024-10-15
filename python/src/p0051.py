"""
Project Euler Problem 51

Again, surprised how effective the brute force solution was

Problem:

By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53,
73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven
primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993.
Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit,
is part of an eight prime value family.
"""
from itertools import combinations, count, product
from typing import List, Tuple

from .lib.primes import is_prime

all_digits = tuple(str(x) for x in range(10))
non_zero = all_digits[1:]
endings = ("1", "3", "7", "9")


def main() -> int:
    for L in count(5):
        largest_possible: int = 10**L
        for Ls in range(1, L - 1):
            for indices in combinations(range(L - 1), Ls):
                mask = ["d"] * L  # d can be replaced by any digit
                for index in indices:
                    mask[index] = "s"  # s can be replaced by any single digit
                valid, smallest = check_mask(mask, largest_possible, L, Ls)
                if valid:
                    return smallest
    return -1  # pragma: no cover


def check_mask(mask: List[str], largest_possible: int, L: int, Ls: int) -> Tuple[bool, int]:
    for start, middle, end in product(non_zero, product(all_digits, repeat=(L - Ls - 2)), endings):
        digits = (start, *middle, end)
        current = mask.copy()
        for digit in digits:
            current[current.index("d")] = digit
        valid = 0
        smallest = largest_possible
        if current[0] == "s":
            selection = non_zero
        else:
            selection = all_digits
        for s in selection:
            new = [x if x != "s" else s for x in current]
            num = int("".join(new))
            if is_prime(num):
                valid += 1
                smallest = min(smallest, num)
            elif 10 - int(s) + valid <= 8:
                break
        else:
            return True, smallest
    return False, 0
