"""
Project Euler Problem 37

I was surprised how fast my brute-force solution went, but it worked

Problem:

The number 3797 has an interesting property. Being prime itself, it is possible
to continuously remove digits from left to right, and remain prime at each
stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797,
379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to
right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
"""
from .lib.primes import is_prime, primes


def main() -> int:
    answer = count = 0
    for p in primes():
        if count == 11:
            break
        elif p < 10:
            continue
        else:
            right = left = p
            while is_prime(right):
                right = right // 10
            if right != 0:
                continue
            while is_prime(left):
                x = 10
                while x < left:
                    x *= 10
                left %= x // 10
            if left != 0:
                continue
            print(p)
            answer += p
            count += 1
    return answer
