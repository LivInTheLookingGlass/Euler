"""
Project Euler Problem 79

Problem:

A common security method used for online banking is to ask the user for three random characters from a passcode.
For example, if the passcode was 531278, they may ask for the 2nd, 3rd, and 5th characters; the expected reply
would be: 317.

The text file, keylog.txt, contains fifty successful login attempts.

Given that the three characters are always asked for in order, analyse the file so as to determine the shortest
possible secret passcode of unknown length.
"""
from collections import defaultdict
from functools import reduce
from typing import DefaultDict, List, Set

from .lib.utils import get_data_file


def main() -> int:
    dependencies: DefaultDict[int, Set[int]] = defaultdict(set)
    for line in get_data_file("p0079_keylog.txt").splitlines():
        x, y, z = (int(i) for i in line)
        dependencies[x].add(y)
        dependencies[y].add(z)

    dep_iter = iter(dependencies.values())
    smallest_set = next(dep_iter)
    for s in dependencies.values():
        if len(s) < len(smallest_set):
            smallest_set = s

    passcode: List[int] = list(smallest_set)
    while dependencies:
        for i, d in dependencies.copy().items():
            if all(n in passcode for n in d):
                passcode.insert(0, i)
                del dependencies[i]

    return reduce(lambda x, y: x * 10 + y, passcode)
