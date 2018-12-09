from pytest import fixture, mark
from umsgpack import load
from sys import argv
from typing import Any

from p0007 import is_prime, primes

answers = {
    1: 233168,          2: 4613732,         3: 6857,            4: 906609,
    5: 232792560,       6: 25164150,        7: 104743,          8: 23514624000,
    9: 31875000,        10: 142913828922,
    13: 5537376230,     14: 837799,                             16: 1366,
    17: 21124,                              19: 171,            20: 648,
    21: 31626,          22: 871198282,      23: 4179871,        24: 2783915460,
    25: 4782,                               27: -59231,
    29: 9183,                               31: 73682,          32: 45228,
    33: 100,            34: 40730,          35: 55,             36: 872187,


                                            47: 134043,


                                            59: 107359,


                                            71: 428570,
    73: 7295372,        74: 402,



                                                                92: 8581146,

    97: 8739992577,
                        206: 1389019170
}

prime_position = mark.first if "-c" in argv else mark.last


@fixture(params=sorted(answers.keys()))
def key(request):  # type: ignore
    return request.param


@prime_position
def test_is_prime() -> None:
    with open('primes.mpack', 'rb') as f:
        set_of_primes = load(f)
    last = 2
    for x, y in zip(primes(), set_of_primes):
        assert is_prime(x)
        assert x == y
        for z in range(last + 1, x):
            assert not is_prime(z)
        last = x


def test_problem(benchmark: Any, key: int) -> None:
    module = __import__("p{:04}".format(key))
    assert benchmark(module.main) == answers[key]
