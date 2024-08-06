from importlib import import_module
from sys import modules
from time import perf_counter_ns
from typing import Callable, Dict, Union

from . import lib

__all__ = ['lib']
problems: Dict[int, Callable[[], Union[int, str]]] = {}

for i in range(1, 10000):
    try:
        name = f'p{i:04}'  # noqa
        module = import_module(f'.{name}', __name__)
        setattr(modules[__name__], name, module)
        __all__.append(name)
        problems[i] = module.main
    except ImportError:
        pass


def run_problems() -> None:  # pragma: no cover
    for i, p in problems.items():
        start = perf_counter_ns()
        answer = p()
        stop = perf_counter_ns()
        print(f'The answer to problem {i:04} is {answer!r} (found in {(stop - start) / 1000:,}μs)')  # noqa
