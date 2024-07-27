"""
Project Euler Template

In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and down, is indicated in bold red and is equal to 2427.
<uncopyable>

Find the minimal path sum from the top left to the bottom right by only moving right and down in matrix.txt (right click and "Save Link/Target As..."), a 31K text file containing an 80 by 80 matrix.
"""
from pathlib import Path
from typing import List, MutableMapping, Sequence


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
    matrix: Sequence[Sequence[int]] = []
    setup: List[Sequence[int]] = []
    with Path(__file__).parent.parent.joinpath('_data', 'p0081_matrix.txt').open('r') as f:
        for raw_line in f.readlines():
            line = raw_line.rstrip('\n')
            setup.append(tuple(int(x) for x in line.split(',')))
    return min_path_sum(tuple(setup), {})


if __name__ == '__main__':
    print(main())  # pragma: no cover
