"""
Project Euler Problem 76

I ended up having to do this with recursion, which I normally do not like to
use that much. Small changes can have large effects on later results. Still,
this seems to work for the moment.

Problem:

It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two
positive integers?
"""
from typing import List


def main() -> int:
    answer = 0
    counts: List[int] = [0] * 101
    counts[1] = 100
    while not counts[100]:
        total = sum(counts)
        counts[1] += 1
        if total > 100:
            idx = 1
            while total > 100:
                counts[idx] = 0
                idx += 1
                counts[idx] += idx
                total = sum(counts)
            counts[1] = 100 - total
        elif total == 100:
            answer += 1
    return answer


if __name__ == '__main__':
    print(main())
