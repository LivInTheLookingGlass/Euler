"""
Project Euler Problem 76

I ended up needing to do this iteratively. The solution is kinda non-intuitive, but it ends up that you are counting
the different summations in-place, as opposed to the recursive solutions I tried at first which used way too much
memory to be workable.

Revision 1:

Revised this to store values instead of numeral counts, so I do no multiplication now

Revision 2:

Optimized this a bit to keep counts[1] as close to the missing piece as possible

Revision 3:

Applied an optimization I found on the C side. Turns out, the number of solutions to a + 2b + n = 100, where
a, b, n in [0, 100] is (100 - n) / 2 + 1. Additionally, I ported the optimization from Revision 2 to work in the case
of the 2s count. These together brought runtime down from ~6m 40s -> ~1m 15s.

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
    total = counts[2] = 100
    while not counts[100]:
        counts[2] += 2
        if total >= 100:
            answer += (100 + counts[2] - total) // 2
            counts[2] = 0  # because I can't do-while
            counts[3] += 3
            idx = 3
            total = sum(counts)
            while total > 100:
                counts[idx] = 0
                idx += 1
                counts[idx] += idx
                total = sum(counts)
            counts[2] = 100 - total - (total % 2)
        total = sum(counts)
    return answer


if __name__ == '__main__':
    print(main())
