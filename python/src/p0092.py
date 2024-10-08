"""
Project Euler Problem 92

I had to approach this by modifying the factors function from p0003, but it
seemed to work fairly well.

Problem:

A number chain is created by continuously adding the square of the digits in a
number to form a new number until it has been seen before.

For example,

44 → 32 → 13 → 10 → 1 → 1
85 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58 → 89

Therefore any chain that arrives at 1 or 89 will become stuck in an endless
loop. What is most amazing is that EVERY starting number will eventually arrive
at 1 or 89.

How many starting numbers below ten million will arrive at 89?
"""
from typing import MutableMapping

from .lib.iters import digits


def f(n: int, cache: MutableMapping[int, int]) -> int:
    if n in cache:
        return cache[n]
    result = sum(x**2 for x in digits(n))
    cache[n] = result
    return result


def main() -> int:
    answer = 0
    cache: MutableMapping[int, int] = {}
    for x in range(2, 10000000):
        while x not in (1, 89):
            x = f(x, cache)
        if x == 89:
            answer += 1
    return answer
