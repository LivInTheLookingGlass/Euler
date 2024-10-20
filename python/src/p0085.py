"""
Project Euler Problem 85

Problem:

By counting carefully it can be seen that a rectangular grid measuring 3 by 2 contains eighteen rectangles:

.. image:: https://projecteuler.net/resources/images/0085.png

Although there exists no rectangular grid that contains exactly two million rectangles, find the area of the grid with the nearest solution.
"""
from math import ceil, sqrt


def num_rectangles(x: int, y: int) -> int:
    answer = 0
    for a in range(1, x + 1):
        for b in range(1, y + 1):
            answer += (x - a + 1) * (y - b + 1)
    return answer


def main(tolerance: int = 2) -> int:
    for x in range(1, ceil(sqrt(2000000))):
        for y in range(1, x):
            if abs(num_rectangles(x, y) - 2000000) <= tolerance:
                return x * y
    return -1
