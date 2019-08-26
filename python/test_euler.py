from pytest import fail, fixture, mark
from umsgpack import load
from sys import argv
from typing import Any

import cython

from p0007 import is_prime, primes

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
    47: 134043,
    48: 9110846700,
    49: 296962999629,
    50: 997651,
    53: 4075,
    59: 107359,
    67: 7273,
    71: 428570,
    73: 7295372,
    74: 402,
    87: 1097343,
    92: 8581146,
    97: 8739992577,
    123: 21035,
    134: 18613426663617118,
    187: 17427258,
    206: 1389019170
}

known_slow = {187}
# this is the set of problems where I have the right answer but wrong solution

prime_position = mark.first if "-c" in argv else mark.last


@fixture(params=sorted(answers.keys()))
def key(request):  # type: ignore
    return request.param


@prime_position
def test_is_prime(benchmark) -> None:
    @cython.ccall
    @cython.locals(
        last=cython.ulonglong,
        x=cython.ulonglong,
        y=cython.ulonglong,
        z=cython.ulonglong
    )
    @cython.returns(None)
    def func(set_of_primes):
        last = 2
        for x, y in zip(primes(), set_of_primes):
            assert is_prime(x)
            assert x == y
            for z in range(last + 1, x):
                assert not is_prime(z)
            last = x

    with open('primes.mpack', 'rb') as f:
        set_of_primes = load(f)
    benchmark.pedantic(func, args=(set_of_primes, ), iterations=1, rounds=1)
    if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 4 * 60:
        fail("Exceeding 5min!")


def test_problem(benchmark: Any, key: int) -> None:
    module = __import__("p{:04}".format(key))
    if key in known_slow:
        assert answers[key] == benchmark.pedantic(
            module.main, iterations=1, rounds=1
        )
    else:
        assert answers[key] == benchmark(module.main)
    if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 60:
        fail("Exceeding 60s!")
