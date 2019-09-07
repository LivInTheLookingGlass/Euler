from functools import partial
from os import remove
from os.path import expanduser
from platform import processor
from subprocess import call, check_call, check_output

from pytest import fail, fixture

answers = {
    1: 233168
}

known_slow = {}
# this is the set of problems where I have the right answer but wrong solution


# to make sure the benchmarks sort correctly
@fixture(params=("{:04}".format(x) for x in sorted(answers)))
def key(request):  # type: ignore
    return request.param


def test_problem(benchmark, key):
    key_i = int(key)
    filename = "p{}.c".format(key)
    exename = "p{}.{}".format(key, processor() or 'exe')
    if call(['which', 'termux-setup-storage']) == 0:
        exename = "{}/{}".format(expanduser("~"), exename)
        # Termux can't make executable files outside of $HOME
    else:
        exename = "./{}".format(exename)
    try:
        check_call(['gcc', '-Werror', '-std=c11', filename, '-o', exename])
        run_test = partial(check_output, [exename])

        if key_i in known_slow:
            assert answers[key_i] == int(benchmark.pedantic(
                run_test, iterations=1, rounds=1
            ).strip())
        else:
            assert answers[key_i] == int(benchmark(run_test).strip())
        # sometimes benchmark disables itself, so check for .stats
        if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 60:
            fail("Exceeding 60s!")
    finally:
        try:
            remove(exename)
        except Exception:
            pass
