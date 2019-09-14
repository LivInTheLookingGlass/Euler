from functools import partial
from os import remove
from os.path import expanduser
from platform import processor
from subprocess import call, check_call, check_output

from pytest import fail, fixture

answers = {
    1: 233168,
    2: 4613732,
    3: 6857,
    5: 232792560,
    6: 25164150,
    7: 104743,
    10: 142913828922,
    76: 190569291,
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
    in_termux = not call(['command', '-v', 'termux-setup-storage'], shell=True)
    if processor():
        exename = "p{}.{}".format(key, processor())
    elif in_termux:
        exename = "p{}.{}".format(key, check_output('lscpu').split()[1])
        # processor() doesn't seem to work on Termux
    else:
        exename = "p{}.exe".format(key)
    if in_termux:
        exename = "{}/{}".format(expanduser("~"), exename)
        # Termux can't make executable files outside of $HOME
    else:
        exename = "./{}".format(exename)
    try:
        check_call([
            'gcc',
            filename,
            '-O',
            '-lm',
            '-Werror',
            '-std=c11',
            '-o',
            exename
        ])
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
