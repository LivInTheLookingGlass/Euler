"""
Project Euler Template

In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and
down, is indicated in bold red and is equal to 2427.

<uncopyable>

Find the minimal path sum from the top left to the bottom right by only moving right and down in matrix.txt (right
click and "Save Link/Target As..."), a 31K text file containing an 80 by 80 matrix.
"""
from typing import List, MutableMapping, Sequence

from lib.utils import get_data_file


def min_path_sum(
    matrix: Sequence[Sequence[int]],
    cache: MutableMapping[Sequence[Sequence[int]], int]
) -> int:
    if matrix in cache:
        return cache[matrix]
    if len(matrix[0]) == 1:
        result = sum(row[0] for row in matrix)
    elif len(matrix) == 1:
        result = sum(matrix[0])
    else:
        result = matrix[0][0] + min(
            min_path_sum(matrix[1:], cache),
            min_path_sum(tuple(row[1:] for row in matrix), cache)
        )
    cache[matrix] = result
    return result


def main() -> int:
    setup: List[Sequence[int]] = []
    for raw_line in get_data_file('p0081_matrix.txt').splitlines():
        line = raw_line.rstrip('\n')
        setup.append(tuple(int(x) for x in line.split(',')))
    return min_path_sum(tuple(setup), {})


if __name__ == '__main__':
    print(main())  # pragma: no cover
