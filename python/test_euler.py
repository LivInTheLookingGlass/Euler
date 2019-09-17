import gc
from shutil import which
from sys import argv
from typing import Any

from pytest import fail, fixture, mark, skip
from umsgpack import load

from p0003 import primes
from p0007 import is_prime

answers = {
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
    59: 107359,
    67: 7273,
    69: 510510,
    71: 428570,
    73: 7295372,
    74: 402,
    76: 190569291,
    77: 71,
    87: 1097343,
    92: 8581146,
    97: 8739992577,
    123: 21035,
    134: 18613426663617118,
    145: 608720,
    187: 17427258,
    206: 1389019170,
}

known_slow = {76, 123, 145}
# this is the set of problems where I have the right answer but wrong solution

prime_position = mark.first if "-c" in argv else mark.last

IN_TERMUX = bool(which('termux-setup-storage'))


@fixture(params=("{:03}".format(x) for x in sorted(answers.keys())))  # to make sure the benchmarks sort correctly
def key(request):  # type: ignore
    return int(request.param)  # reduce processing burden on test


@prime_position
def test_is_prime(benchmark) -> None:
    def func(set_of_primes):
        last = 2
        for x, y in zip(primes(), set_of_primes):
            assert is_prime(x)
            assert x == y
            for z in range(last + 1, x):
                assert not is_prime(z)
            last = x

    with open('primes.mpack', 'rb') as f:
        set_of_primes = load(f)  # set of first million primes
    benchmark.pedantic(func, args=(set_of_primes, ), iterations=1, rounds=1)
    if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > (200 * 1_000_000 / 1_000_000):  # 200ns * primes
        fail("Exceeding 200ns average!")


def test_problem(benchmark: Any, key: int) -> None:
    if IN_TERMUX and key in known_slow:
        skip()
    module = __import__("p{:04}".format(key))
    if key in known_slow:
        answer = benchmark.pedantic(module.main, iterations=1, rounds=1)
    else:
        answer = benchmark(module.main)
    assert answers[key] == answer
    del module
    gc.collect()
    # sometimes benchmark disables itself, so check for .stats
    if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 60:
        fail("Exceeding 60s!")
