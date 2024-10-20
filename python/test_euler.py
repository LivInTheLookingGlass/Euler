from gc import collect as gc_collect
from importlib import import_module
from os import environ
from pathlib import Path
from shutil import which
from sys import path
from typing import Any, Callable, Dict, Iterable, Tuple, Union, cast
from warnings import warn

from pytest import fail, fixture, mark, skip, xfail
from umsgpack import load

PY_FOLDER = Path(__file__).parent
path.append(str(PY_FOLDER))

from src.lib.iters import groupwise  # noqa: E402  # isort:skip
from src.lib.primes import is_prime, primes  # noqa: E402  # isort:skip
from src.lib.utils import get_answer  # noqa: E402  # isort:skip

answers: Dict[int, Union[int, str]] = {
    x: get_answer(x) for x in (
        *range(1, 54),
        *range(55, 61),
        63,
        67,
        *range(69, 75),
        *range(76, 78),
        79,
        81,
        85,
        87,
        89,
        92,
        97,
        99,
        118,
        123,
        134,
        145,
        187,
        206,
        357,
        836,
    )
}

known_slow = {118, 357}
# this is the set of problems where I have the right answer but wrong solution

IN_TERMUX = bool(which('termux-setup-storage'))

_raw_NO_SLOW = environ.get('NO_SLOW')
try:
    _parsed_NO_SLOW: Union[str, int, None] = int(_raw_NO_SLOW)  # type: ignore
except Exception:
    _parsed_NO_SLOW = _raw_NO_SLOW
_raw_ONLY_SLOW = environ.get('ONLY_SLOW')
try:
    _parsed_ONLY_SLOW: Union[str, int, None] = int(_raw_ONLY_SLOW)  # type: ignore
except Exception:
    _parsed_ONLY_SLOW = _raw_ONLY_SLOW
_raw_NO_OPTIONAL_TESTS = environ.get('NO_OPTIONAL_TESTS')
try:
    _parsed_NO_OPTIONAL_TESTS: Union[str, int, None] = int(_raw_NO_OPTIONAL_TESTS)  # type: ignore
except Exception:
    _parsed_NO_OPTIONAL_TESTS = _raw_NO_OPTIONAL_TESTS

if _parsed_NO_SLOW and _parsed_ONLY_SLOW:
    warn(
        "Test suite told to ignore slow tests AND run only slow tests. Ignoring conflicing options"
    )  # pragma: no cover

# if in Termux, default to NO_SLOW, but allow users to explicitly override that decision
NO_SLOW = ((IN_TERMUX and _parsed_NO_SLOW is None) or _parsed_NO_SLOW) and not _parsed_ONLY_SLOW
ONLY_SLOW = _parsed_ONLY_SLOW and not _parsed_NO_SLOW
NO_OPTIONAL_TESTS = (_parsed_NO_OPTIONAL_TESTS is None and ONLY_SLOW) or _parsed_NO_OPTIONAL_TESTS


@fixture(params=("{:0>3}".format(x) for x in sorted(answers.keys())))  # to make sure the benchmarks sort correctly
def key(request) -> int:  # type: ignore
    return int(request.param)  # reduce processing burden on test


@mark.parametrize("group_size_str", ("{:0>2}".format(x) for x in range(2, 65)))
def test_groupwise(benchmark: Any, group_size_str: str) -> None:
    def test_func() -> Iterable[Tuple[int, ...]]:
        return tuple(groupwise(range(10_000 + group_size), group_size))

    if ONLY_SLOW or NO_OPTIONAL_TESTS:
        skip()
    group_size = int(group_size_str)
    groups = benchmark(test_func)
    comparison = tuple(range(10_000 + group_size))  # adding group_size produces an equal number of groups
    for idx, group in enumerate(groups):
        assert group == comparison[idx:idx+group_size]


def test_is_prime(benchmark: Any) -> None:
    def func(set_of_primes: Iterable[int]) -> None:
        last = 2
        for x, y in zip(primes(), set_of_primes):
            assert is_prime(x)
            assert x == y
            for z in range(last + 1, x):
                assert not is_prime(z)
            last = x

    if ONLY_SLOW or NO_OPTIONAL_TESTS:
        skip()
    with PY_FOLDER.joinpath('primes.mpack').open('rb') as f:
        set_of_primes = load(f)  # set of first million primes
    benchmark.pedantic(func, args=(set_of_primes, ), iterations=1, rounds=1)
    if ('PYTEST_XDIST_WORKER' not in environ and
       hasattr(benchmark, 'stats') and benchmark.stats.stats.max > (200 * 1_000_000 / 1_000_000)):  # 200ns * primes
        fail("Exceeding 200ns average!")


def test_problem(benchmark: Any, key: int) -> None:
    if (NO_SLOW and key in known_slow) or (ONLY_SLOW and key not in known_slow):
        skip()
    test_func: Callable[[], Union[int, str]] = import_module("src.p{:0>4}".format(key)).main
    if key in known_slow:
        answer = benchmark.pedantic(test_func, iterations=1, rounds=1)
    else:
        answer = benchmark(test_func)
    assert answers[key] == answer
    del test_func
    gc_collect()
    # sometimes benchmark disables itself, so check for .stats
    if 'PYTEST_XDIST_WORKER' not in environ and hasattr(benchmark, 'stats') and benchmark.stats.stats.median > 60:
        fail_func = cast(Callable[[str], None], xfail if key in known_slow else fail)
        stats = benchmark.stats.stats
        fail_func("Exceeding 60s! (Max={:.6}s, Median={:.6}s)".format(stats.max, stats.median))
