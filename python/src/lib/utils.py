from functools import lru_cache
from pathlib import Path
from typing import Any, Callable, Union, overload

from .iters import digits
from .math import from_digits

try:
    from typing import Literal
except ImportError:
    from typing_extensions import Literal  # type: ignore


@overload
def get_data_file(name: str, mode: Literal['r'] = 'r') -> str: ...
@overload
def get_data_file(name: str, mode: Literal['rb']) -> bytes: ...


@lru_cache(maxsize=None)
def get_data_file(name: str, mode: str = 'r') -> Any:
    """Returns the contents of a file in the top-level _data directory."""
    with Path(__file__).parent.parent.parent.parent.joinpath('_data', name).open(mode) as f:
        return f.read()


def get_answer(n: int) -> Union[int, str]:
    for line in get_data_file('answers.csv').splitlines()[1:]:
        id_, type, size, value = line.split('\t')
        if int(id_) != n:
            continue
        if type == 'str':
            return value
        return int(value)
    raise ValueError()


def is_palindrome(n: Any, rep_func: Callable[[Any], str] = repr) -> bool:
    """Checks if the string representation of an object is a palindrome"""
    r = rep_func(n)
    return r == r[::-1]


def steps_to_palindrome(n: int, depth: int = 0) -> int:
    """Returns a 0 if the number does not reach a palindrome in 50 or fewer steps, otherwise returns the step count"""
    new = n + from_digits(digits(n))
    if is_palindrome(new):
        return depth + 1
    elif depth == 50:
        return 0
    return steps_to_palindrome(new, depth=depth + 1)
