from pytest import fixture
from umsgpack import load

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
    13: 5537376230,
    14: 837799,
    16: 1366,
    20: 648,
    21: 31626,
    22: 871198282,
    25: 4782,
    29: 9183,
}


@fixture(params=answers.keys())
def key(request):  # type: ignore
    return request.param


def test(benchmark, key):
    module = __import__("p{:04}".format(key))
    assert benchmark(module.main) == answers[key]


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
