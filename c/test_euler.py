from os import remove
from platform import processor
from subprocess import check_call, check_output

from pytest import fail, fixture

answers = {
    1: 233168
}

known_slow = {}
# this is the set of problems where I have the right answer but wrong solution


@fixture(params=("{:04}".format(x) for x in sorted(answers.keys())))  # to make sure the benchmarks sort correctly
def key(request):  # type: ignore
    return request.param


def test_problem(benchmark, key):
    key_i = int(key)
    filename = "p{}.c".format(key)
    exename = "p{}.{}".format(key, processor() or 'exe')
    try:
        check_call(['gcc', '-fms-extensions', '-std=c11', filename, '-o', exename])

        def run_test():
            return int(check_output(["./{}".format(exename)]).strip())

        if key_i in known_slow:
            assert answers[key_i] == benchmark.pedantic(
                run_test, iterations=1, rounds=1
            )
        else:
            assert answers[key_i] == benchmark(run_test)
        # sometimes benchmark disables itself, so check for .stats
        if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 60:
            fail("Exceeding 60s!")
    finally:
        try:
            remove(exename)
        except Exception:
            pass
