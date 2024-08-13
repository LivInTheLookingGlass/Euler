"""
Project Euler Problem 42

The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we
form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle
number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common
English words, how many are triangle words?
"""
from typing import Set

from .lib.math import triangle
from .lib.utils import get_data_file


def main() -> int:
    answer = 0
    words = get_data_file('p0042_words.txt', 'rb').replace(b'"', b'').split(b',')
    max_cached_idx: int = 0
    max_cached: int = 0
    cache: Set[int] = set()
    for word in words:
        n = sum(x - 0x40 for x in word)
        while n > max_cached:
            max_cached_idx += 1
            max_cached = triangle(max_cached_idx)
            cache.add(max_cached)
        if n in cache:
            answer += 1
    return answer
