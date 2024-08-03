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

answers: Dict[int, Union[int, str]] = {
    1: 233168,
    2: 4613732,
    3: 6857,
    4: 906609,
    5: 232792560,
    6: 25164150,
    7: 104743,
    8: 23514624000,
    9: 31875000,
    10: 142913828922,
    11: 70600674,
    12: 76576500,
    13: 5537376230,
    14: 837799,
    15: 137846528820,
    16: 1366,
    17: 21124,
    18: 1074,
    19: 171,
    20: 648,
    21: 31626,
    22: 871198282,
    23: 4179871,
    24: 2783915460,
    25: 4782,
    27: -59231,
    28: 669171001,
    29: 9183,
    30: 443839,
    31: 73682,
    32: 45228,
    33: 100,
    34: 40730,
    35: 55,
    36: 872187,
    37: 748317,
    38: 932718654,
    39: 840,
    40: 210,
    41: 7652413,
    42: 162,
    43: 16695334890,
    44: 5482660,
    45: 1533776805,
    46: 5777,
    47: 134043,
    48: 9110846700,
    49: 296962999629,
    50: 997651,
    52: 142857,
    53: 4075,
    55: 249,
    56: 972,
    57: 153,
    58: 26241,
    59: 107359,
    60: 26033,
    67: 7273,
    63: 49,
    69: 510510,
    71: 428570,
    73: 7295372,
    74: 402,
    76: 190569291,
    77: 71,
    81: 427337,
    87: 1097343,
    89: 743,
    92: 8581146,
    97: 8739992577,
    99: 709,
    118: 44680,
    123: 21035,
    134: 18613426663617118,
    145: 608720,
    187: 17427258,
    206: 1389019170,
    357: 1739023853137,
    836: "aprilfoolsjoke",
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
    if 'PYTEST_XDIST_WORKER' not in environ and hasattr(benchmark, 'stats') and benchmark.stats.stats.max > (200 * 1_000_000 / 1_000_000):  # 200ns * primes
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
