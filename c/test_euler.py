from functools import partial
from os import remove
from os.path import expanduser
from platform import processor
from subprocess import call, check_call, check_output

from pytest import fail, fixture, skip

answers = {
    1: 233168,
    2: 4613732,
    3: 6857,
    5: 232792560,
    6: 25164150,
    7: 104743,
    10: 142913828922,
    34: 40730,
    76: 190569291,
}

known_slow = {}
# this is the set of problems where I have the right answer but wrong solution

IN_TERMUX = not call(['command', '-v', 'termux-setup-storage'], shell=True)

if processor():
    EXE_EXT = processor()
elif IN_TERMUX:
    # processor() doesn't seem to work on Termux
    EXE_EXT = check_output('lscpu').split()[1]
else:
    EXE_EXT = "exe"

if IN_TERMUX:
    EXE_TEMPLATE = "{}/p{{}}.{}".format(expanduser("~"), EXE_EXT)
    # Termux can't make executable files outside of $HOME
else:
    EXE_TEMPLATE = "./p{{}}.{}".format(EXE_EXT)

# to make sure the benchmarks sort correctly
@fixture(params=("{:04}".format(x) for x in sorted(answers)))
def key(request):  # type: ignore
    return request.param


def test_problem(benchmark, key):
    key_i = int(key)
    filename = "p{}.c".format(key)
    exename = EXE_TEMPLATE.format(key)
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
            if IN_TERMUX:
                skip()
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
