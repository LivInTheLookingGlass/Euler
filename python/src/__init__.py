from importlib import import_module
from sys import modules
from time import perf_counter
from typing import Callable, Dict, Set, Union

from . import lib

__all__ = ['lib']
problems: Dict[int, Callable[[], Union[int, str]]] = {}
slow: Set[int] = set()

for i in range(1, 10000):
    try:
        name = f'p{i:0>4}'  # noqa
        module = import_module(f'.{name}', __name__)
        setattr(modules[__name__], name, module)
        __all__.append(name)
        if hasattr(module, 'main'):
            problems[i] = module.main
        if getattr(module, 'is_slow', False):
            slow.add(i)
    except ImportError:
        pass


def run_problems() -> None:  # pragma: no cover
    for i, p in problems.items():
        start = perf_counter()
        answer = p()
        stop = perf_counter()
        print(f'The answer to problem {i:0>4} is {answer!r} (found in {(stop - start) * 1000:,}ms)')  # noqa
