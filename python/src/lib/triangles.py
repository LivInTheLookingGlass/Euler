from itertools import tee
from typing import Sequence


def reduce_triangle(triangle: Sequence[Sequence[int]]) -> int:
    centering = (len(triangle[-1]) + 1)
    potential_totals = [0] * centering
    for parent in reversed(triangle):
        head1, head2 = tee(iter(potential_totals))
        next(head2, None)
        potential_totals = [max((x, y)) + z for x, y, z in zip(head1, head2, parent)]
    return potential_totals[0]
